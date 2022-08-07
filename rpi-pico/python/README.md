# RPI PicoW - Tram display

## Install

This is specific to macos intel

### Micropython

In order to run python program on it

1. Plug in BOOTSEL your RPi PicoW
2. Download latest [PicoW Micropython UF2](https://micropython.org/download/rp2-pico-w/rp2-pico-w-latest.uf2)
3. Copy through your explorer to your device

### USB connection

Install `minicom`

Then run:

```sh
# /dev/cu.usbmodem14101 is an example
minicom -o -D /dev/cu.usbmodem14101
```

You can soft reset with `CTRL-D`
