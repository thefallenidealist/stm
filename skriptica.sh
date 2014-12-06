#!/bin/sh

# ispisi samo ako ima .c fajl

#echo $POPIS

NAME=main
DEFINES="-DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER"
DIRS="-Isrc -Isrc/lib -I."

#POPIS=` clang35 -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -Isrc -Isrc/lib -MM src/main.c | sed 's/main.o://g' | tr ' ' '\n' | tr -d '\' | sed '/^\s*$/d'`
POPIS=`clang35 $DEFINES $DIRS -MM src/$NAME.c | sed 's/$NAME.o://g' | tr ' ' '\n' | tr -d '\' | sed '/^\s*$/d'`

<<COM
for i in $POPIS; 
do
	n=`echo $i | sed 's/\.h/\.c/g'`
	if [ -f $n ]; 	then
		echo $n | sed 's/\.c/\.o/g'
	fi;
done
COM

for i in $POPIS; do n=`echo $i | sed 's/\.h/\.c/g'` ; if [ -f $n ]; then echo $n | sed 's/\.c/\.x/g'; fi; done
