/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "pico/bootrom.h"
void reboot()
{
    reset_usb_boot(0, 0);
}

int main() {
    stdio_init_all();
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }
    int cnt = 0;

    printf("ESC to reboot\n\n");

    while (true)
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(250);

        int c = getchar_timeout_us(0);
        if (c >= 0)
        {
            if (c == 27)
                reboot();       // connect with PUTTY
                // sudo dmesg | grep tty
                //   e.g. /dev/ttyS0   115200
        }                

        cnt++;
        printf("cnt:%d\n", cnt);
        // sudo picotool load -x build/picow_blink.elf
        // next: wait for command sent to device
        // putty -serial /dev/ttyACM0 -sercfg 115200,8,n,1,N

    }
    
}
