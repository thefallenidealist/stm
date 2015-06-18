#!/bin/sh
# ispisat ce fajlove koji trebaju za main.c
# ispisat ce te fajlove samo ako header ukljucen u main.c ima svoj .c fajl
# TODO ovo bi zapravo trebalo bit u Makefileu, ali ne znam napravit

NAME=main
MCU=$1

if [ "$MCU" = "F4" ]; then
	DEFINES="-DSTM32F4XX -DUSE_STDPERIPH_DRIVER"
	DIRS="-Isrc -Isrc/lib -Isrc/lib/f4 -I."
elif [ "$MCU" = "F1" ]; then
	DEFINES="-DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER"
	DIRS="-Isrc -Isrc/lib -Isrc/lib/f1 -I."
elif [ "$MCU" = "M8" ]; then
	DEFINES="-DAVR"
	DIRS="-Isrc -Isrc/lib -Isrc/avr -I. -I/usr/local/avr/include"
elif [ "$MCU" = "M16" ]; then	# isto kao i gore
	DEFINES="-DAVR"
	DIRS="-Isrc -Isrc/lib -Isrc/avr -I. -I/usr/local/avr/include"
elif [ "$MCU" = "M328" ]; then	# isto kao i gore
	DEFINES="-DAVR"
	DIRS="-Isrc -Isrc/lib -Isrc/avr -I. -I/usr/local/avr/include"
else
	echo "ERROR, nije zadana arhitektura ili je zadano krivo, izlazim"
	exit
fi

POPIS=`clang36 $DEFINES $DIRS -MM src/$NAME.c | sed 's/$NAME.o://g' | tr ' ' '\n' | tr -d '\' | sed '/^\s*$/d'`
# POPIS: 
# src/main.c
# src/newlib_stubs.h
# src/clang_patch.h
# ...

for i in $POPIS;
do 
	n=`echo $i | sed 's/\.h/\.c/g'`		# pretvori sve .h u .c
	if [ -f $n ]; then 					# ako je file npr src/clang_patch.c
		echo $n | sed 's/\.c/\.x/g'		# promijeni mu ekstenziju u .x
	fi; 
done
