// see https://github.com/Kosmokleaner/RapidPicoC

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "pico/bootrom.h"

int main()
{
    stdio_init_all();
	// needed?
    if (cyw43_arch_init())
	{
        printf("Wi-Fi init failed");
        return -1;
    }
    int cnt = 0;

    printf("ESC to reboot\n\n");

    while (true)
    {
		// toggle 0 / 1 state to blink LED
#ifdef CYW43_WL_GPIO_LED_PIN
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, cnt % 2);
#else
		gpio_put(PICO_DEFAULT_LED_PIN, cnt % 2);
#endif

        sleep_ms(250);

		// connect with PUTTY for keyboard input
        int c = getchar_timeout_us(0);
		// press ESC to reboot
        if (c == 27)
            reset_usb_boot(0, 0); // reboot

		char* CPU = "?";
#ifdef __ARM_ARCH_8M_MAIN__
    // Cortex-M33 (RP2350 ARM core)
	CPU = "ARM";
#endif
#ifdef __riscv
	CPU = "RISC-V";
#endif

        cnt++;
        printf("cnt:%d CPU:%s\n", cnt, CPU);
		// connect with PUTTY for output
    }
}
