
# Rapid Pico C

<img width="315" height="106" alt="ezgif-71ae7d307d8e3e63" src="https://github.com/user-attachments/assets/84b03f22-d1a9-49c9-b2e1-816c5d42931b" />


This is a "Raspberry Pi Pico 2" C/C++ starter project (in/out ), optimized for iteration time (no USB plugin and button pressing).
This is much better than the standard method (unplug cable, plug in cable while pressing button, drag and drop .uf2 file) - for convience and speed. The setup work is still improvable. Feedback is welcome.

Key lines for best iteration:
```
  ./build.sh
  sudo picotool load -x build/picow_blink.elf
  putty -serial /dev/ttyACM0 -sercfg 115200,8,n,1,N
```

You can use the host PC keyboard and see the output in a window:

<img width="507" height="132" alt="puttyText" src="https://github.com/user-attachments/assets/9582c295-363f-4874-8e2f-24e1f6ad407f" />

## Why Raspberry Pi Pico 2 W

The ~7$ hardware features a ARM(2-core) and RISC-V(2-core) at 150 MHz, 520KB SRAM and 4MB Flash memory. It's tiny and low power which means you can use USB or a battery and no need for a fan. You can get the Wifi + Bluetooth variant (W) which I did but mind the code to address the LED needs minor adjustment. You start programming with Python and play with cheap attachable custom hardware (displays, sound in/out, buttons, motors, sensors). If you need more performance you can program in C/C++ or assembly. No OS (it's a Micro controller, no Micro processor) or other services make the performance very stable. Simple coprocessors can be used for custom tasks e.g. output 15bit color to a VG display. The older Pico 1 specs are a bit lower but suitable for most use cases.

## Hardware and Software requirements

<img width="364" height="233" alt="IMG_9676" src="https://github.com/user-attachments/assets/24508288-692b-4556-8fdb-56a19b8ef924" />


* USB data cable (USB power cable is not enough)
* Raspberry Pi Pico 2 W (RP2350, Wifi)
* Tested on Ubuntu x64, should be easy to adapt to other OS
* Text editor or IDE e.g. VSCode, Notepad++ (yes, that is an option on Ubuntu)

# How to the code locally

* Get the code from the terminal is one option (into Documents/code/RapidPicoC)
```
  cd ~/Documents
  mkdir code
  cd code
  git clone git@github.com:Kosmokleaner/RapidPicoC.git
  cd RapidPicoC
  chmod +x clean.sh
  chmod +x build.sh
```

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

* compile and link
```
  ./build.sh
```
* for profiling the build time
```
  time ./build.sh
```
 
## Method 1: Simple upload (physical, needed the first time): bootsel

* If needed, unplug Raspberry Pi Pico from USB (Pico side is fragile connection, better to other side)
* While pushing button on Pico, plug in USB data cable (to put the device into bootsel mode)
* A new device should appear in "Files", if not, the cable might not be a "data" cable 
* Find the output file in build/<name>.uf2
* Drag and drop the file to the device

## Method 2: Better itertion time for upload: using picotool

We need "picotool" and I found prebuilt versions but none had the required USB support compiled in. 

* If needed / once
```
  cd ~/Documents/code
  git clone --recursive https://github.com/raspberrypi/pico-sdk.git
  export PICO_SDK_PATH=~/Documents/code/pico-sdk
  sudo apt install build-essential cmake pkg-config libusb-1.0-0-dev
  cd ~/Documents
  mkdir code
  cd code
  git clone https://github.com/raspberrypi/picotool.git
  cd picotool
  mkdir build
  cd build
  cmake -DCMAKE_BUILD_TYPE=Release ..
  cmake --build . -j$(nproc)
```

You should be able to run the picotool from the build folder. You can reference it like this: 
```
  ~/Documents/code/picotool/build/picotool
```
For more convenience you can make a symbolic link (export does not work with sudo and path adds unwanted files)
```
  sudo ln -s ~/Documents/code/picotool/build/picotool /usr/local/bin/picotool
```

* upload (works only if in bootsel mode)
```
  sudo picotool load -x build/picow_blink.elf
```
  To quickly get back into bootself mode use Putty and press ESC, see C code:
```
  reset_usb_boot(0, 0);
```

## Keyboard input and text output 
* If needed, install Putty SSH client
```
  putty -serial /dev/ttyACM0 -sercfg 115200,8,n,1,N
```

* to find connection settings, likely: /dev/ttyS0 115200
```
  sudo dmesg | grep tty
```

* Start Putty from terminal
```
  putty -serial /dev/ttyACM0 -sercfg 115200,8,n,1,N
```

* Or start Putty from terminal from Apps

<img width="341" height="319" alt="puttyUI" src="https://github.com/user-attachments/assets/e4fef307-3f3c-405b-a085-f6a6e60625ed" />

* The app has USB stdin/stdout support because of the following lines in CMakeList.txt
```
  pico_enable_stdio_usb(picow_blink 1)
  pico_enable_stdio_uart(picow_blink 0)
```

## How to adapt for RISC-V

The Raspberry Pico 2 has a ARM and a RiscV CPU, you can choose which one to target with compiler settings.

* Currently the code is setup to compile for "ARM Cortex-M33 core" as can be seen in the compile log: 
```
  Pico Platform (PICO_PLATFORM) is 'rp2350-arm-s'.
```

 rp2350-arm-s → ARM Cortex-M33 (Secure)<br>
 rp2350-arm-ns → ARM Cortex-M33 (Non-Secure)<br>
 rp2350-riscv → Hazard3 RISC-V core

* Install the RISV-V compiler once
```
  kdir -p ~/.pico-sdk/riscv
  cd ~/.pico-sdk/riscv
  wget https://github.com/raspberrypi/pico-sdk-tools/releases/download/v2.0.0-5/riscv-  toolchain-14-x86_64-lin.tar.gz
  tar xf riscv-toolchain-14-x86_64-lin.tar.gz
```
* run ./clear.sh
* Change the CMakeList.txt, uncomment those lines
```
set(PICO_TOOLCHAIN_PATH ~/.pico-sdk/riscv)
set(PICO_PLATFORM rp2350-riscv)
```

## How to adapt for Pico 1 or Pico 2 or no Wifi
! untested !

Adjust the following line (_w is for Wifi)
```
set(PICO_BOARD pico2_w CACHE STRING "Board type")
```


## Todo
* First printf don't reach PuTTY, fix without adding delay
* RISC-V compile mode
* Measure and optimize for time
* sudo needs password, how not need this?
* Fix code for non Wifi model and Pico 1
* Pictures, screenshots
* Make putty line part of .sh 




 
