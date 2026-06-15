#include "platform.h"


const char* getCompiledInstructionSet()
{
    const char* ret = "?";
#ifdef __ARM_ARCH_8M_MAIN__
    // Cortex-M33 (RP2350 ARM core)
	ret = "ARM";
#endif
#ifdef __riscv
	ret = "RISC-V";
#endif
    return ret;
}
