
# Rapid Pico C

Tested on Raspberry Pi Pico 2 (RP2350)

By adjusting the compiler setting this should work for Raspberry Pi Pico (RP2040) as well.



## Hardware
* USB data cable (USB power cable is not enough)
* Tested on Ubuntu x64, should be easy to adapt to other OS

## Build

* compile and link
  > build.sh
* for profiling
  > time ./build.sh
 
## Method 1: Simple upload (physical)

* If needed, unplug Raspberry Pi Pico from USB (Pico side is fragile connection, better to other side)
* While pushing button on Pico, plug in USB data cable
* A new device should appear in "Files", if not, the cable might not be a "data" cable 
* Find the output file in build/<name>.uf2
* Drag and drop the file to the device

## Method 2: Better itertion time for upload: Pictool upload

We need the picotool and I found prebuilt version but none had the USB support compiled
in. 

* If needed
  > sudo apt install build-essential cmake pkg-config libusb-1.0-0-dev
  > git clone https://github.com/raspberrypi/picotool.git
  > cd picotool
  > mkdir build
  > cd build
  > cmake -DCMAKE_BUILD_TYPE=Release ..
  > cmake --build . -j$(nproc)





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




 
