# created 141129
NAME	= main

CC  	= clang35
#DIR_TOOLS	= /usr/local/gcc-arm-embedded-*/
# linker ne voli * nit tabovi nit komentare u bilo cemu sto ima varijablu za njega. Linker je pizda.
DIR_TOOLS	= /usr/local/gcc-arm-embedded-4_8-2014q3-20140805
LD  	= $(DIR_TOOLS)/bin/arm-none-eabi-ld
OBJCOPY = $(DIR_TOOLS)/bin/arm-none-eabi-objcopy
SIZE	= $(DIR_TOOLS)/bin/arm-none-eabi-size

DIR_OBJ = ./obj
DIR_BIN = ./bin

TARGET	= -target thumb-unknown-eabi		# clang
ARCH	= armv7-m
CPU	= -mcpu=cortex-m3 
DEFINES	= -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER 
OPTS	= -O0 -g
#OPTS	= -O2
DIRS 	=  -Isrc \
	   -Isrc/lib\
	   -I.
COMMON_FLAGS 	 = $(TARGET) $(CPU) $(OPTS) -nostdlib -mfloat-abi=soft -Wall
CCFLAGS 	 = $(COMMON_FLAGS) $(DEFINES) $(DIRS) -fno-short-enums -Wall
ASFLAGS 	 = $(COMMON_FLAGS) 

LD_DIRS		 = -L$(DIR_TOOLS)/lib/gcc/arm-none-eabi/4.8.4/armv7-m	#libgcc
LD_DIRS		+= -L$(DIR_TOOLS)/arm-none-eabi/lib/armv7-m 		# libc, libm
LINKER_FILE = $(wildcard src/lib/*.ld)
LD_FLAGS = -nostartfiles -nostdlib -nostartupfiles --gc-sections  \
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

SRC_S = $(wildcard src/lib/*.s)
#SRC_C = $(DEPEND_C:.x=.c) 	# ne smije ovo bit, inace duplicira OBJ
SRC_C += src/newlib_stubs.c

# makni foldere, dodaj prefix, preimenuj .x u .o
OBJS = $(addprefix $(DIR_OBJ)/, $(notdir $(DEPEND_C:.x=.o)))
OBJS += $(addprefix $(DIR_OBJ)/, $(notdir  $(SRC_S:.s=.o)))	# assembler fajl nije nigdje stavljen, al treba
OBJS += $(addprefix $(DIR_OBJ)/, $(notdir  $(SRC_C:.c=.o)))	# newlib fajl nije nigdje stavljen, al treba

#@$(CC) -MM $(CCFLAGS) $< > $(DIR_OBJ)/$*.d


$(NAME).elf: $(OBJS)
	@printf "\t\t Linking to ELF\n"
	@$(LD) $(LD_FLAGS) -o $(DIR_BIN)/$(NAME).elf
	@printf "\t\t size:\n"
	@$(SIZE) $(DIR_BIN)/$(NAME).elf
	@printf "\t\t Stripping binary\n"
	@$(OBJCOPY) -O binary $(DIR_BIN)/$(NAME).elf $(DIR_BIN)/$(NAME).bin

# compile and generate dependency info
#obj/%.o: src/%.c
$(DIR_OBJ)/%.o: src/%.c
	@printf "\t\t Kuvam src $<\n"
	@$(CC) $(CCFLAGS) -c -o $@ $<

$(DIR_OBJ)/%.o: src/lib/%.c
	@printf "\t\t Kuvam lib $<\n"
	@$(CC) $(CCFLAGS) -c -o $@ $<

$(DIR_OBJ)/%.o: src/lib/%.s
	@printf "\t\t Kuvam ass $<\n"
	@$(CC) $(ASFLAGS) -o $@ -c $<

env:
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

print-depend:
	@echo $(DEPEND_C)
	
clean:
	@printf "\t\t Cleaning\n"
	@rm -f $(DIR_OBJ)/*.o $(DIR_BIN)/$(NAME)* $(DIR_OBJ)/*.d

upload:
	./upload.sh
