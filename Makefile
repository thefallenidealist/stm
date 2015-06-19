# created 141129
# 150518	sredjeno multiarch za ARM (F1 i F4)
# ovo koristi FreeBSDov stdio.h, stdint.h, unistd.h i sl. newlib-ov printf je zakurac
# -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
# INFO primjer: gmake MCU=F4		MCU=F4 gg

NAME	= main


ifeq ($(MCU), F1)
	ARM = 1
endif
ifeq ($(MCU), F4)
	ARM = 1
endif
ifeq ($(MCU), AVR)
	ARM = 0
	AVR = 1
endif

DIR_TOOLS	= /usr/local/bin
TOOLS_PREFIX = arm-none-eabi
CC  	= clang36

#ifeq ($(ARM), 1)
#TOOLS_PREFIX = arm-none-eabi
#CC  	= clang36
#endif
#ifeq ($(AVR), 1)
#TOOLS_PREFIX = avr
#CC = avr-gcc
#endif
LD  		= $(DIR_TOOLS)/$(TOOLS_PREFIX)-ld
OBJCOPY 	= $(DIR_TOOLS)/$(TOOLS_PREFIX)-objcopy
SIZE		= $(DIR_TOOLS)/$(TOOLS_PREFIX)-size

DIR_OBJ 	= ./obj
DIR_BIN 	= ./bin

ifeq ($(ARM), 1)
TARGET	= -target thumb-unknown-eabi	# needed for clang
CPU		= -mcpu=cortex-m3 
#CPU	= -mcpu=cortex-m4 	# TODO
DEFINES	= -DUSE_STDPERIPH_DRIVER 
endif

#OPTS	= -O0 -g
#OPTS	= -O1 -g
OPTS	= -O1
#OPTS	= -O2 -g
#OPTS	= -O2 -g
#OPTS	= -O3 -g

DIRS 	=	-I src \
			-I.

ifeq ($(MCU), F4)
	ARCH	= armv7e-m
	DIRS	+= -I src/lib/f4
	DEFINES += -DSTM32F4XX -DSTM32F4
	LINKER_FILE		= src/lib/f4/stm32.ld
	SRC_S	= $(wildcard src/lib/f4/*.s)
	OPENOCD = openocd -f openocd4.cfg -c init -c targets -c "reset halt" -c "flash erase_check 0" -c " flash write_image erase bin/main.bin 0x08000000" -c "reset run" -c "shutdown"
endif
ifeq ($(MCU), F1)
	ARCH	= armv7-m
	DIRS	+= -I src/lib/f1
	DEFINES	+= -DSTM32F10X_MD -DSTM32F1
	LINKER_FILE		= src/lib/f1/stm32.ld
	SRC_S	= $(wildcard src/lib/f1/*.s)
	OPENOCD = openocd -f openocd1.cfg -c init -c targets -c "reset halt" -c "flash write_image erase bin/main.bin 0x08000000" -c "reset run" -c "shutdown"
endif

# INFO objasnjenja
# -mno-thumb-interwork		# nemoj koristit ARM i Thumb zajedno	# default GCC
# -mlittle-endian			# default GCC
# -mtune=cortex-m4
# -ffunction-sections 		# smanji	nemaju nekog pretjeranog utjecaja te opcije
# -fdata-sections 			# smanji
# --gc-sections 			# nije za clang
# -ffreestanding 			# da nema warning za void main(void)
# -ffreestanding			# Indicated that the file should be compiled for a freestanding enviroment (like a kernel), not a hosted (userspace), environment.
# -fno-short-enums 			# znalo posluzit sa starim GCCom i newlibom
# -fno-builtin				# Disable special handling and optimizations of builtin functions like strlen and malloc.
# -nostdlib					# Disables standard library
# -nostdinc					# Makes sure the standard library headers are not included.
# -nostdinc++				# Makes sure the standard C++ library headers are not included. This makes sense if you build a custom version of libc++ and want to avoid including system one. 
# -ferror-limit=1 			# da stane nakon prvog #error
# -pedantic					# Warn on language extensions.			my code isn't ready yet for this
#TODO -flto remove unused functions
# --sysroot /dev/null TODO

#CLANG_FLAGS	 = $(TARGET) -Wformat -Wmissing-prototypes -ferror-limit=1 
CLANG_FLAGS	 = $(TARGET) -Wformat -Wmissing-prototypes
#GCC_FLAGS 	 = -std=c99 -mthumb -mno-thumb-interwork -fno-common -fno-strict-aliasing -fmessage-length=0 -fno-builtin -Wp,-w 

# ako je newlib sa hardFP INFO
#COMMON_FLAGS 	 = $(CPU) $(OPTS) -nostdlib -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Wall $(CLANG_FLAGS) 
#COMMON_FLAGS 	 = $(CPU) $(OPTS) -nostdlib -mfloat-abi=soft -Wall $(CLANG_FLAGS) -ffreestanding -fno-builtin -nostdinc
COMMON_FLAGS 	 = $(CPU) $(OPTS) -nostdlib -mfloat-abi=soft -Wall $(CLANG_FLAGS)

CCFLAGS 	 = $(COMMON_FLAGS) $(DEFINES) $(DIRS) \
						-ffreestanding 
ASFLAGS 	 = $(COMMON_FLAGS) 

LD_DIRS 		= -L src/lib/toolchain/$(ARCH)		# libc, libm, libgcc

LD_FLAGS 	 = -nostartfiles -nostdlib -nostartupfiles --gc-sections \
				--no-enum-size-warning \
				-Map $(DIR_BIN)/$(NAME).elf.map \
				-T $(LINKER_FILE) \
				$(LD_DIRS) $(OBJS) \
				--start-group -lgcc -lc -lm --end-group 

# pronadji jel postoji .c fajl umjesto .x (nisu svi fajlovi u paru .h/.c)
# XXX kludge
DEPEND_C = $(shell ./skriptica.sh $(MCU))
# $(patsubst %.c,%.o,$(wildcard *.c))
DEPEND_C2 = $(patsubst %.x,%.c,$(DEPEND_C))	# replace .x with .c

# makni foldere, dodaj prefix, preimenuj .x u .o	npr: ./obj/main.o, ./obj/newlib_stubs.o
OBJS  = $(addprefix $(DIR_OBJ)/, $(notdir $(DEPEND_C:.x=.o)))
OBJS += $(addprefix $(DIR_OBJ)/, $(notdir $(SRC_S:.s=.o)))	# dodaj i assembler startup file

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

ifeq ($(MCU), F1)
$(DIR_OBJ)/%.o: src/lib/f1/%.c
endif
ifeq ($(MCU), F4)
$(DIR_OBJ)/%.o: src/lib/f4/%.c
endif
	@printf "\t\t Kuvam lib $<\n"
	@$(CC) $(CCFLAGS) -c -o $@ $<

ifeq ($(MCU), F1)
$(DIR_OBJ)/%.o: src/lib/f1/%.s
endif
ifeq ($(MCU), F4)
$(DIR_OBJ)/%.o: src/lib/f4/%.s
endif
	@printf "\t\t Kuvam ass $<\n"
	@$(CC) $(ASFLAGS) -o $@ -c $<

env:
	@echo Debug pizdarije
	@echo SRC_S:
	@echo $(SRC_S)
	@echo ""

	@echo DEPEND_C:
	@echo $(DEPEND_C)
	@echo ""

	@echo DEPEND_C2:
	@echo $(DEPEND_C2)
	@echo ""

	@echo OBJS:
	@echo $(OBJS)
	@echo ""

	@echo MY_VAR:
	@echo $(MY_VAR)
	@echo ""

clean:
	@printf "\t\t Cleaning\n"
	@rm -f $(DIR_OBJ)/*.o $(DIR_BIN)/$(NAME)* $(DIR_OBJ)/*.d

upload:
#	./upload.sh
	@echo Uploading
	$(OPENOCD)

# TODO upload, da moze snimit flash sa mikrokontrolera


# We can change the list of C source files into a list of object files by replacing the ‘.c’ suffix with ‘.o’ in the result, like this: 
# $(patsubst %.c,%.o,$(wildcard *.c))
# Thus, a makefile to compile all C source files in the directory and then link them together could be written as follows: 
# objects := $(patsubst %.c,%.o,$(wildcard *.c))
# foo : $(objects)
#	cc -o foo $(objects)
