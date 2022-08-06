export PICO_SDK_PATH=/Users/skelz0r/sandbox/pico-sdk

cd build/
cmake ..
make || exit

picotool reboot -u -f
picotool load main.uf2

echo "picotool reboot -a && sleep 1 && minicom -b 115200 -o -D /dev/cu.usbmodem14101" | pbcopy

cd ..
