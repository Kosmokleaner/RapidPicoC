#pragma once

#include <stdint.h> // uint32_t

void asm_init();

uint32_t get_cycles();

// @return "ARM", "RISC-V" or "?"
const char* getCompiledInstructionSet();
