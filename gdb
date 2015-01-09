# starta se na 4242 portu, v2 protokol
st-link
arm-eabi-gdb main.elf
target extended-remote:4242
load
continue


####
openocd
telnet localhost 4444
	reset halt
arm-none-eabi-gdb -tui --eval-command="target remote localhost:3333" main.elf

#gdb komande
mon reg
s	# single step
info frame	# stanje registara
si

C-x C-a      
C-x 1
C-x 2

layout src
layout asm	# memorijske adrese
layout split

focus next | prev | src | asm | regs | split | cmd
winheight name +count
winheight reg -8
