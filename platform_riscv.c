#include "platform.h"

#ifdef __riscv

static inline void init_cycle_counter()
{
    // Read mcountinhibit CSR (controls counters)
    uint32_t mcountinhibit;

    __asm__ volatile ("csrr %0, mcountinhibit" : "=r"(mcountinhibit));

    // Clear CY bit (bit 0) to enable mcycle
    mcountinhibit &= ~1u;

    __asm__ volatile ("csrw mcountinhibit, %0" :: "r"(mcountinhibit));
}

uint32_t get_cycles()
{
    uint32_t cycles;
    __asm__ volatile (
        "rdcycle %0" : "=r"(cycles)
    );
    return cycles;
}

void asm_init()
{
    init_cycle_counter();
}

#endif // __riscv

