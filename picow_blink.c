// RapicPicoC
// https://github.com/Kosmokleaner/RapidPicoC
// Version 1.0

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "pico/bootrom.h"

#include "platform.h"

int main()
{
    asm_init();

    stdio_init_all();

	// call is needed for Wifi model, return argument 
    bool wifiInit = cyw43_arch_init();

	// for non Wifi model
#ifndef CYW43_WL_GPIO_LED_PIN
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
#endif
	
    int cnt = 0;

    while (true)
    {
		// toggle 0 / 1 state to blink LED
#ifdef CYW43_WL_GPIO_LED_PIN
		cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, cnt % 2);
#else
		gpio_put(PICO_DEFAULT_LED_PIN, cnt % 2);
#endif

        sleep_ms(250);

        static bool stdinConnected = false;
        if(!stdinConnected && stdio_usb_connected())
        {
            stdinConnected = true;

            printf("Press ESC to reboot (into BOOTSEL mode)\n\n");
            printf("  CPU:'%s'\n", getCompiledInstructionSet());
            printf("  wifiInit:'%d'\n", (int)wifiInit);
            // 4 on Raspberry Pi Pico
            printf("  sizeof(void*):%d\n", sizeof(void*));
        }

        // connect with PUTTY for keyboard input and printf output

        int c = getchar_timeout_us(0);

        // press ESC to reboot
        if (c == 27)
            reset_usb_boot(0, 0); // reboot
	
        cnt++;
        printf("cnt:%d cycles:%u\n", cnt, get_cycles());
    }
}
