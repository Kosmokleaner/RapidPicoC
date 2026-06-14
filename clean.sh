echo "clean"
# r:remove folder, f:force, print no error
rm -rf build
rm -rf CMakeFiles
rm -rf generated
rm -rf pico-sdk
rm -f CMakeCache.txt
rm -f cmake_install.cmake
rm -f compile_commands.json
rm -f Makefile
rm -f pico_flash_region.ld 

# need to plug in Pico into USB while button pressed 
# sudo picotool load -x build/picow_blink.elf


