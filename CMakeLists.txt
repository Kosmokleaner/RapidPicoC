# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

# "ARM" or "RISCV"
set(MY_CPU_TARGET "ARM")

####################################################################

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2_w CACHE STRING "Board type")
#set(PICO_BOARD pico_w CACHE STRING "Board type")

# uncomment to target RISC-V instead of ARM CPU. Install compiler before:
# mkdir -p ~/.pico-sdk/riscv
# cd ~/.pico-sdk/riscv
# wget https://github.com/raspberrypi/pico-sdk-tools/releases/download/v2.0.0-5/riscv-toolchain-14-x86_64-lin.tar.gz
# tar xf riscv-toolchain-14-x86_64-lin.tar.gz
if(MY_CPU_TARGET STREQUAL "RISCV")
set(PICO_TOOLCHAIN_PATH ~/.pico-sdk/riscv)
set(PICO_PLATFORM rp2350-riscv)
endif()


# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(picow_blink C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(picow_blink
        picow_blink.c
        )
target_link_libraries(picow_blink
        pico_stdlib              # for core functionality
        pico_cyw43_arch_none     # we need Wifi to access the GPIO, but we don't need anything else
        )

# allow USB connection to PUTTY (printf and getchar inpuut)
pico_enable_stdio_usb(picow_blink 1)
pico_enable_stdio_uart(picow_blink 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(picow_blink)


# add url via pico_set_program_url
