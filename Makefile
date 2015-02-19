# created 141129
NAME	= main

# promijenit i dolje COMMON_FLAGS
CC  	= clang36
#CC	= arm-none-eabi-gcc
# ne moze se if koristit izvan recepta
UNAME := $(shell uname -m)	# varijabla iz shella

#DIR_TOOLS	= /usr/local/gcc-arm-embedded-*/
# linker ne voli * nit tabovi nit komentare u bilo cemu sto ima varijablu za njega. Linker je pizda.
DIR_TOOLS	= /usr/local/gcc-arm-embedded-4_8-2014q3-20140805
LD  	= $(DIR_TOOLS)/bin/arm-none-eabi-ld
#LD	= ld.gold
OBJCOPY = $(DIR_TOOLS)/bin/arm-none-eabi-objcopy
SIZE	= $(DIR_TOOLS)/bin/arm-none-eabi-size

DIR_OBJ = ./obj
DIR_BIN = ./bin

TARGET	= -target thumb-unknown-eabi
ARCH	= armv7-m
CPU	= -mcpu=cortex-m3 
#CPU	= -mcpu=cortex-m4 
	# STM32F1
	#DEFINES	= -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER 
# STM32F4
DEFINES	= -DSTM32F4XX -DUSE_STDPERIPH_DRIVER 
#OPTS	= -O0 -g	# XXX ne radi
#OPTS	= -O1 -g 
#OPTS	= -O2 -g 
OPTS	= -O2
#OPTS	= -O3 -g
DIRS 	=  -Isrc \
	   -Isrc/lib/f4\
	   -I.

# clang
#COMMON_FLAGS 	 = $(TARGET) $(CPU) $(OPTS) -nostdlib -mfloat-abi=soft -Wall
#TODO -flto remove unused functions
CLANG_FLAGS	 = $(TARGET) 
# INFO ne radi sa sysroot iako ga usmjerim u folder gdje su headeri /usr/local/gcc-arm-embedded-4_8-2014q3-20140805/arm-none-eabi
#CLANG_FLAGS	 = $(TARGET)  --sysroot /dev/null -I/usr/local/gcc-arm-embedded-4_8-2014q3-20140805/arm-none-eabi/include \
#-I/usr/local/gcc-arm-embedded-4_8-2014q3-20140805/lib/gcc/arm-none-eabi/4.8.4/include
GCC_FLAGS 	 = -std=c99 -mthumb -mno-thumb-interwork -fno-common -fno-strict-aliasing -fmessage-length=0 -fno-builtin -Wp,-w 
# -Wmissing-prototypes 
# F1
COMMON_FLAGS 	 = $(CPU) $(OPTS) -nostdlib -mfloat-abi=soft -Wall $(CLANG_FLAGS) -DDEBUG
#COMMON_FLAGS 	 = $(CPU) $(OPTS) -nostdlib -mfloat-abi=soft -Wall $(CLANG_FLAGS) 
# F4
#COMMON_FLAGS 	 = $(CPU) $(OPTS) -nostdlib -mfloat-abi=hard -Wall $(CLANG_FLAGS)  
CCFLAGS 	 = $(COMMON_FLAGS) $(DEFINES) $(DIRS) -fno-short-enums \
		   -ffreestanding	# void main(void)
ASFLAGS 	 = $(COMMON_FLAGS) 

# F1
LD_DIRS		 = -L$(DIR_TOOLS)/lib/gcc/arm-none-eabi/4.8.4/armv7-m	#libgcc
LD_DIRS		+= -L$(DIR_TOOLS)/arm-none-eabi/lib/armv7-m 		# libc, libm
# F4
#LD_DIRS		 = -L$(DIR_TOOLS)/lib/gcc/arm-none-eabi/4.8.4/armv7-m	#libgcc
#LD_DIRS		+= -L$(DIR_TOOLS)/arm-none-eabi/lib/armv7e-m 		# libc, libm
#LINKER_FILE 	 = $(wildcard src/lib/*.ld)
	# STM32F1
	#LINKER_FILE 	 = $(wildcard src/lib/f1/*.ld)
# STM32F4
LINKER_FILE 	 = $(wildcard src/lib/f4/*.ld)


# -nostartupfiles	ne linka crt*.o objektne fajlove
# --gc-sections ne smije bit za GCC
#LD_FLAGS 	 = -nostartfiles -nostdlib -nostartupfiles --gc-sections 
#LD_FLAGS 	 = -nostartfiles -nostdlib -nostartupfiles 
LD_FLAGS 	 = -nostdlib \
		   --no-enum-size-warning \
		   -Map $(DIR_BIN)/$(NAME).elf.map  -T $(LINKER_FILE)  \
		   $(LD_DIRS) $(OBJS) \
             --start-group -lgcc -lc -lm --end-group 

# mora bit izvan recepata
# mora bit :=, valjda onda samo jednom pokrene i ne razjebe sve ostalo
# nadji koji sve headeri trebaju mainu i uredi malo ispis
# promijeni .c i .h u .x radi lakseg kasnije pretvaranja u .o
# TODO napravit da ne $(NAME) ne mora bit u src nego da ga sam nadje bilo gdje u $(DIRS)
# XXX razjebe se jer nema stm32f10x.c nego samo .h
#DEPENDCIES := $(shell $(CC) $(DEFINES) $(DIRS) -MM src/$(NAME).c | sed 's/main.o: //g' | sed 's/\\//g' | sed 's/\../\.x/g' )

# pronadji jel postoji .c fajl umjesto .x (nisu svi fajlovi u paru .h/.c)
# XXX jebacki kludge
DEPEND_C = $(shell ./skriptica.sh)

#DEPEND_C = $(shell for i in $DEPENDCIES; do n=`echo $i | sed 's/\.h/\.c/g'` ; if [ -f $n ]; then echo $n | sed 's/\.c/\.x/g'; fi; done )
#DEPEND_C = $(shell NAME=$(NAME) for VAR in $(DEPENDCIES); do echo $(NAME); done )	# XXX nece uopce ispisat $(VAR), al oce konstantu

#SRC_S = $(wildcard src/lib/*.s)
	# STM32F1
	#SRC_S = $(wildcard src/lib/f1/*.s)
# STM32F4
SRC_S = $(wildcard src/lib/f4/*.s)
#SRC_C = $(DEPEND_C:.x=.c) 	# ne smije ovo bit, inace duplicira OBJ
#SRC_C += src/newlib_stubs.c

# makni foldere, dodaj prefix, preimenuj .x u .o
OBJS = $(addprefix $(DIR_OBJ)/, $(notdir $(DEPEND_C:.x=.o)))
OBJS += $(addprefix $(DIR_OBJ)/, $(notdir  $(SRC_S:.s=.o)))	# assembler fajl nije nigdje stavljen, al treba
OBJS += $(addprefix $(DIR_OBJ)/, $(notdir  $(SRC_C:.c=.o)))	# newlib fajl nije nigdje stavljen, al treba

#@$(CC) -MM $(CCFLAGS) $< > $(DIR_OBJ)/$*.d

$(NAME).elf: $(OBJS)
	@printf "\t\t kompajler: $(CC)\n"
	@printf "\t\t Linking to ELF\n"
	@$(LD) $(LD_FLAGS) -o $(DIR_BIN)/$(NAME).elf
	@printf "\t\t size:\n"
	@$(SIZE) $(DIR_BIN)/$(NAME).elf
	@printf "\t\t Stripping binary\n"
	@$(OBJCOPY) -O binary $(DIR_BIN)/$(NAME).elf $(DIR_BIN)/$(NAME).bin

# compile and generate dependency info
$(DIR_OBJ)/%.o: src/%.c
	@printf "\t\t Kuvam src $<\n"
	@$(CC) $(CCFLAGS) -c -o $@ $<

$(DIR_OBJ)/%.o: src/lib/f4/%.c
	@printf "\t\t Kuvam lib $<\n"
	@$(CC) $(CCFLAGS) -c -o $@ $<

# STM32F4
$(DIR_OBJ)/%.o: src/lib/f4/%.s
	@printf "\t\t Kuvam ass $<\n"
	@$(CC) $(ASFLAGS) -o $@ -c $<

env:
	@echo UNAME:
	@echo $(UNAME)
	@echo SRC_C:
	@echo $(SRC_C)
	@echo ""

	@echo SRC_S:
	@echo $(SRC_S)
	@echo ""

	@echo OBJS:
	@echo $(OBJS)
	@echo ""

	@echo DEPENDCIES:
	@echo $(DEPENDCIES)
	@echo ""

	@echo DEPEND_C:
	@echo $(DEPEND_C)
	@echo TMP:
	@echo $(TMP)
	@echo ""
	@echo $(PWD)

clean:
	@printf "\t\t Cleaning\n"
	@rm -f $(DIR_OBJ)/*.o $(DIR_BIN)/$(NAME)* $(DIR_OBJ)/*.d

upload:
	./upload.sh
