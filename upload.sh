#####
echo "upload.sh"
# USART
#stm32flash -w main.bin /dev/cuaU0
#####
# SWD

#(echo reset init; echo reset halt ; echo flash erase_check 0; echo flash write_image erase bin/main.bin 0x08000000 ; echo reset run ; sleep 8; killall nc) | nc localhost 4444
(echo reset init; echo reset halt ; echo flash erase_check 0; echo flash write_image erase bin/main.bin 0x08000000 ; echo reset halt; echo reset run ; sleep 8; killall nc) | nc localhost 4444
