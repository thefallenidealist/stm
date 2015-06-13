#!/bin/sh
# created 150518

if [ "$1" = "F4" ]; then
	MCU=F4 gmake
	killall openocd
	nohup openocd -f openocd4.cfg&
	./upload.sh
else
	echo "Error, pogresna arhitektura"
fi
