
# Rapid Pico C

Raspberry Pi Pico C starter project optimized for iteration time (no USB plugin and button pressing).

Tested on Raspberry Pi Pico 2 W (RP2350, Wifi)

By adjusting the compiler setting this should work for Raspberry Pi Pico (RP2040) as well.

The Raspberry Pico 2 has a AMD and a RiscV CPU, you can choose which one to target with compiler settings.


* Currently the code is setup to compile for "ARM Cortex-M33 core" as can be seen in the compile log: 
  > Pico Platform (PICO_PLATFORM) is 'rp2350-arm-s'.

 rp2350-arm-s → ARM Cortex-M33 (Secure)
 rp2350-arm-ns → ARM Cortex-M33 (Non-Secure)
 rp2350-riscv → Hazard3 RISC-V core

* to change this look for the following line in CMakeList.txt
  > set(PICO_BOARD pico2_w CACHE STRING "Board type")

## Hardware and Software
* USB data cable (USB power cable is not enough)
* Raspberry Pi Pico
* Tested on Ubuntu x64, should be easy to adapt to other OS

# How to the code locally

* Get the code from the terminal is one option (into Documents/code/RapidPicoC)
  > cd ~/Documents
  > mkdir code
  > cd code
  > git clone git@github.com:Kosmokleaner/RapidPicoC.git
  > cd RapidPicoC
  > chmod +x clean.sh
  > chmod +x build.sh

## C code explained

* On board LED blinking, keyboard input and text output

```
  // init
  stdio_init_all();
  if (cyw43_arch_init()) { printf("Wi-Fi init failed"); return -1; }

  while (true)
  {
     // wifi LED, change for non W model
     cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, cnt % 2);
     sleep_ms(250);
   		// connect with PUTTY for keyboard input
     int c = getchar_timeout_us(0);
     if (c == 27)
         reset_usb_boot(0, 0); // reboot
     cnt++;
     // connect with PUTTY for output
     printf("cnt:%d\n", cnt); 
  }
```

## Build

* todo PICO_SDK_PATH

* compile and link
  > ./build.sh
* for profiling
  > time ./build.sh
  e.g. ...
  > real 0m0.612s
  > user 0m0.334s
  > sys	 0m0.281s

 
## Method 1: Simple upload (physical)

* If needed, unplug Raspberry Pi Pico from USB (Pico side is fragile connection, better to other side)
* While pushing button on Pico, plug in USB data cable
* A new device should appear in "Files", if not, the cable might not be a "data" cable 
* Find the output file in build/<name>.uf2
* Drag and drop the file to the device

## Method 2: Better itertion time for upload: Pictool upload

We need the picotool and I found prebuilt version but none had the USB support compiled
in. 

* If needed / once
  > sudo apt install build-essential cmake pkg-config libusb-1.0-0-dev
  > git clone https://github.com/raspberrypi/picotool.git
  > cd picotool
  > mkdir build
  > cd build
  > cmake -DCMAKE_BUILD_TYPE=Release ..
  > cmake --build . -j$(nproc)

* upload
  > sudo picotool load -x build/picow_blink.elf

## Keyboard input and text output 
* If needed, install Putty SSH client
  > putty -serial /dev/ttyACM0 -sercfg 115200,8,n,1,N

* to find connection settings, likely: /dev/ttyS0 115200
  > sudo dmesg | grep tty

* Start Putty from terminal
  > putty -serial /dev/ttyACM0 -sercfg 115200,8,n,1,N

* Or start Putty from terminal from Apps

<img width="341" height="319" alt="puttyUI" src="https://github.com/user-attachments/assets/e4fef307-3f3c-405b-a085-f6a6e60625ed" />

* The app has USB stdin/stdout support because of the following lines in CMakeList.txt
  > pico_enable_stdio_usb(picow_blink 1)
  > pico_enable_stdio_uart(picow_blink 0)

## Todo
* setup
  > source martin.sh
  > 
  > export PICO_SDK_PATH=/home/username/Documents/code/picoaudio/pico-sdk
  > export PICO_EXTRAS_PATH=/home/username/Documents/code/picoaudio/pico-extras
  > export PICO_EXAMPLES_PATH=/home/username/Documents/code/picoaudio/pico-examples
  > export PICOTOOL_FETCH_FROM_GIT_PATH=/home/username/Documents/code/picotool
  > export PICO_PLATFORM=rp2350-arm-s
  > export PICO_BOARD=pico2
  > export PICO_TOOLCHAIN_PATH=/usr/bin
  > #export PICO_COMPILER=arm-none-eabi-gcc
  > unset PICO_COMPILER

* Fix for non Wifi model and Pico 1
* pictures, screenshots

## References
* prebuilt picotool (missing USB support)
  [1](https://github.com/raspberrypi/picotool)
  [2](https://github.com/raspberrypi/pico-sdk-tools/releases)
* [Raspberry Pi Documentation](https://www.raspberrypi.com/documentation/microcontrollers/?version=5A09D5312E22)




 
