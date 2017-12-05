#!/bin/sh

# openocd -f openocd4.cfg		prvo pozvat
GDB=/usr/local/gcc-arm-embedded-4_9-2015q1-20150306/bin/arm-none-eabi-gdb


(echo reset halt ; killall nc) | nc localhost 4444

$GDB -tui --eval-command="target remote localhost:3333" bin/main.elf
