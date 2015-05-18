# created 141129
# ovo koristi FreeBSDov stdio.h, stdint.h, unistd.h i sl. newlib-ov printf je zakurac
# -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
# INFO primjer: gmake MCU=F4		MCU=F4 gg

NAME	= main

# promijenit i dolje COMMON_FLAGS
CC  	= clang36
#CC	= arm-none-eabi-gcc

DIR_TOOLS	= /usr/local/bin
LD  		= $(DIR_TOOLS)/arm-none-eabi-ld
OBJCOPY 	= $(DIR_TOOLS)/arm-none-eabi-objcopy
SIZE		= $(DIR_TOOLS)/arm-none-eabi-size

DIR_OBJ 	= ./obj
DIR_BIN 	= ./bin

TARGET	= -target thumb-unknown-eabi	# needed for clang
CPU		= -mcpu=cortex-m3 
#CPU	= -mcpu=cortex-m4 	# TODO

DEFINES		= -DUSE_STDPERIPH_DRIVER 
#OPTS	= -O0 -g	# XXX ne radi
#OPTS	= -O1 -g 
#OPTS	= -O2 -g 
OPTS	= -O2 -g
#OPTS	= -O3 -g

DIRS 	=	-I src \
			-I.

ifeq ($(MCU), F4)
	ARCH	= armv7e-m
	DIRS	+= -I src/lib/f4
	DEFINES += -DSTM32F4XX
	LINKER_FILE		= src/lib/f4/stm32.ld
	SRC_S	= $(wildcard src/lib/f4/*.s)
endif
ifeq ($(MCU), F1)
	ARCH	= armv7-m
	DIRS	+= -I src/lib/f1
	DEFINES	+= -DSTM32F10X_MD
	LINKER_FILE		= src/lib/f1/stm32.ld
	SRC_S	= $(wildcard src/lib/f1/*.s)
endif

# INFO objasnjenja
# -mno-thumb-interwork		# nemoj koristit ARM i Thumb zajedno	# default GCC
# -mlittle-endian			# default GCC
# -mtune=cortex-m4
# -ffunction-sections 		# smanji	nemaju nekog pretjeranog utjecaja te opcije
# -fdata-sections 			# smanji
# --gc-sections 			# nije za clang
# -ffreestanding 			# da nema warning za void main(void)
# -fno-short-enums 			# znalo posluzit sa starim GCCom i newlibom

# ako je newlib sa hardFP INFO
#COMMON_FLAGS 	 = $(CPU) $(OPTS) -nostdlib -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Wall $(CLANG_FLAGS) 
#COMMON_FLAGS 	 = $(CPU) $(OPTS) -nostdlib -mfloat-abi=soft -Wall $(CLANG_FLAGS) -ffreestanding -fno-builtin -nostdinc
COMMON_FLAGS 	 = $(CPU) $(OPTS) -nostdlib -mfloat-abi=soft -Wall $(CLANG_FLAGS)

# clang
#TODO -flto remove unused functions
CLANG_FLAGS	 = $(TARGET) -Wformat -Wmissing-prototypes 
# --sysroot /dev/null TODO
#GCC_FLAGS 	 = -std=c99 -mthumb -mno-thumb-interwork -fno-common -fno-strict-aliasing -fmessage-length=0 -fno-builtin -Wp,-w 


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


# makni foldere, dodaj prefix, preimenuj .x u .o
OBJS  = $(addprefix $(DIR_OBJ)/, $(notdir $(DEPEND_C:.x=.o)))
OBJS += $(addprefix $(DIR_OBJ)/, $(notdir  $(SRC_S:.s=.o)))	# assembler fajl nije nigdje stavljen,
						#al treba, nece javit gresku ako je zakomentirano, al program nece radit

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
	@echo SRC_S:
	@echo $(SRC_S)
	@echo ""

	@echo OBJS:
	@echo $(OBJS)
	@echo ""

	@echo DEPEND_C:
	@echo $(DEPEND_C)
	@echo TMP:
	@echo $(TMP)
	@echo ""

clean:
	@printf "\t\t Cleaning\n"
	@rm -f $(DIR_OBJ)/*.o $(DIR_BIN)/$(NAME)* $(DIR_OBJ)/*.d

upload:
	./upload.sh

