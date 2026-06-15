#include "platform.h"

#ifdef __arm__

#define DWT_CTRL   (*(volatile uint32_t *)0xE0001000)
#define DWT_CYCCNT (*(volatile uint32_t *)0xE0001004)
#define DEMCR      (*(volatile uint32_t *)0xE000EDFC)

#define DEMCR_TRCENA      (1u << 24)
#define DWT_CYCCNTENA     (1u << 0)

void init_cycle_counter()
{
    DEMCR |= DEMCR_TRCENA;
    DWT_CYCCNT = 0;
    DWT_CTRL |= DWT_CYCCNTENA;
}

uint32_t get_cycles()
{
    // C implementation
//    return DWT_CYCCNT;

   // ARM assembply implementation
   uint32_t val;
    __asm__ volatile (
        "ldr %0, =0xE0001004\n"
        "ldr %0, [%0]\n"
        : "=r"(val)
    );
    return val;
}

void asm_init()
{
    init_cycle_counter();
}

#endif // #ifdef __arm__

