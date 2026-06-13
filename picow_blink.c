// see https://github.com/Kosmokleaner/RapidPicoC

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "pico/bootrom.h"

int main()
{
    stdio_init_all();
	// needed?
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }
    int cnt = 0;

    printf("ESC to reboot\n\n");

    while (true)
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, cnt % 2);
        sleep_ms(250);

		// connect with PUTTY for keyboard input
        int c = getchar_timeout_us(0);
		// press ESC to reboot
        if (c == 27)
            reset_usb_boot(0, 0); // reboot

        cnt++;
        printf("cnt:%d\n", cnt);
        // sudo picotool load -x build/picow_blink.elf
        // next: wait for command sent to device
        // putty -serial /dev/ttyACM0 -sercfg 115200,8,n,1,N
    }
}
