#!/bin/sh

(echo reset halt ; killall nc) | nc localhost 4444

arm-none-eabi-gdb -tui --eval-command="target remote localhost:3333" bin/main.elf
