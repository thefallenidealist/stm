#!/bin/sh

# ispisi samo ako ima .c fajl

#echo $POPIS

NAME=main

MCU=$1
#echo "MCU kao argument je: $MCU"

if [ "$MCU" = "F4" ]; then
	DEFINES="-DSTM32F4XX -DUSE_STDPERIPH_DRIVER"
	DIRS="-Isrc -Isrc/lib -Isrc/lib/f4 -I."
elif [ "$MCU" = "F1" ]; then
	DEFINES="-DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER"
	DIRS="-Isrc -Isrc/lib -Isrc/lib/f1 -I."
else
	echo "ERROR, nije zadana arhitektura ili je zadano krivo, izlazim"
	exit
fi

#POPIS=` clang36 -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -Isrc -Isrc/lib -MM src/main.c | sed 's/main.o://g' | tr ' ' '\n' | tr -d '\' | sed '/^\s*$/d'`
POPIS=`clang36 $DEFINES $DIRS -MM src/$NAME.c | sed 's/$NAME.o://g' | tr ' ' '\n' | tr -d '\' | sed '/^\s*$/d'`

#for i in $POPIS; do n=`echo $i | sed 's/\.h/\.c/g'` ; if [ -f $n ]; then echo $n | sed 's/\.c/\.x/g'; fi; done
for i in $POPIS;
do 
	n=`echo $i | sed 's/\.h/\.c/g'`
	if [ -f $n ]; then 
		echo $n | sed 's/\.c/\.x/g'
	fi; 
done
