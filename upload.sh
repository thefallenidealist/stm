#####
echo "upload.sh"
# USART
#stm32flash -w main.bin /dev/cuaU0
#####
# SWD
#(echo init ; echo reset init ; echo halt ; echo flash write_image erase main.bin 0x08000000 ; echo reset run ; sleep 4; killall nc) | nc localhost 4444
#killall openocd && openocd&
(echo init ; echo reset init ; echo halt ; echo flash write_image erase bin/main.bin 0x08000000 ; echo reset run ; sleep 5; killall nc) | nc localhost 4444

