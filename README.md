
# Rapid Pico C

Tested on Raspberry Pi Pico 2 W (RP2350, Wifi)

By adjusting the compiler setting this should work for Raspberry Pi Pico (RP2040) as well.



## Hardware
* USB data cable (USB power cable is not enough)
* Tested on Ubuntu x64, should be easy to adapt to other OS

## C code explained

* On board USB blinking

```
  // init
  stdio_init_all();
  if (cyw43_arch_init()) { printf("Wi-Fi init failed"); return -1; }

  int flip = 0;
  while (true)
  {
     // wifi LED, change for non W model
     cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, flip);
     flip = 1 - flip;
     sleep_ms(250);
   		// connect with PUTTY for keyboard input
     int c = getchar_timeout_us(0);
     if (c == 27)
         reset_usb_boot(0, 0); // reboot
     cnt++;
     printf("cnt:%d\n", cnt); // printout to see app running when connected to Putty 
  }
```

## Build

* compile and link
  > build.sh
* for profiling
  > time ./build.sh
  e.g.
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

* to find connection settings, likely: /dev/ttyS0 115200
  > sudo dmesg | grep tty


* upload
  > sudo picotool load -x build/picow_blink.elf



## Keyboard input and text output 
* If needed, install Putty SSH client
  > putty -serial /dev/ttyACM0 -sercfg 115200,8,n,1,N

## Todo
* setup
  > export PICO_SDK_PATH=/home/username/Documents/code/picoaudio/pico-sdk
* pictures, screenshots

## References
* prebuilt picotool (missing USB support)
  [1](https://github.com/raspberrypi/picotool)
  [2](https://github.com/raspberrypi/pico-sdk-tools/releases)
* [Raspberry Pi Documentation](https://www.raspberrypi.com/documentation/microcontrollers/?version=5A09D5312E22)




 
