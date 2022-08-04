export PICO_SDK_PATH=/Users/skelz0r/sandbox/pico-sdk

cd build/
cmake ..
make
picotool reboot -u
picotool load blink.uf2
picotool reboot -a

echo "minicom -b 115200 -o -D /dev/cu.usbmodem14101" | pbcopy

cd ..

