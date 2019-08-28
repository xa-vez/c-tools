RESULT ?= schedule

# user definitions
DEFINES = \


# include directories
INCLUDES  :=                                      \
	-I../../../../common/                         \
	-I../../../../tools/etc/src/date-time/        

# asm sources
ASM_SOURCES =

# c sources
C_SOURCES :=                                      \
	../src/main.c                                 \
	../src/schedule.c                             \
	../../../../common/debug.c                    \
	../../../../tools/etc/src/date-time/date-time.c 

# headers
HEADERS :=                                        \
	../../../../common/debug_settings.h           \
	../../../../common/debug.h                    \
	../../../../common/types.h                    \
	../../../../tools/etc/src/date-time/date-time.h \

ASM_OBJECTS = $(patsubst %.S, %.o, $(ASM_SOURCES))

C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))

OUTPUT_DIR = output
OBJ_DIR = $(OUTPUT_DIR)/obj

LINKER_SCRIPT =

CFLAGS += -fno-common -Wall -O0 -g3 -ffunction-sections -fdata-sections -Wl,-M=$(OUTPUT_DIR)/$(RESULT).map
#CFLAGS += -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
#CFLAGS +=  # -T$(LINKER_SCRIPT)
CFLAGS += $(DEFINES)
CFLAGS += $(INCLUDES)

#CROSS_COMPILE ?= arm-none-eabi-
CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJDUMP = $(CROSS_COMPILE)objdump
OBJCOPY = $(CROSS_COMPILE)objcopy
SIZE = $(CROSS_COMPILE)size

THIS_MAKEFILE := $(lastword $(MAKEFILE_LIST))

all: build size

build: $(RESULT) $(RESULT).lst $(RESULT).bin
	
$(RESULT): $(ASM_OBJECTS) $(C_OBJECTS) $(HEADERS) $(LINKER_SCRIPT) $(THIS_MAKEFILE)
	$(CC) $(CFLAGS) $(addprefix $(OBJ_DIR)/, $(notdir $(ASM_OBJECTS))) $(addprefix $(OBJ_DIR)/, $(notdir $(C_OBJECTS))) -o $(OUTPUT_DIR)/$@

$(ASM_OBJECTS): | $(OBJ_DIR)

$(C_OBJECTS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $@

%.o: %.c $(HEADERS) $(THIS_MAKEFILE)
	$(CC) $(CFLAGS) -c $< -o $(addprefix $(OBJ_DIR)/, $(notdir $@))

%.o: %.S $(HEADERS) $(THIS_MAKEFILE)
	$(CC) $(CFLAGS) -c $< -o $(addprefix $(OBJ_DIR)/, $(notdir $@))

%.lst: %
	$(OBJDUMP) -x -S $(OUTPUT_DIR)/$(RESULT) > $(OUTPUT_DIR)/$@

%.bin: %
	$(OBJCOPY) -O binary $(OUTPUT_DIR)/$< $(OUTPUT_DIR)/$@

# size rule
size: 
	size $(OUTPUT_DIR)/$(RESULT)

# clean rule
clean:
#	rm -f $(RESULT).elf
#	rm -f $(RESULT).bin
#	rm -f $(RESULT).lst
#	rm -f $(RESULT).map
	rm -rf $(OUTPUT_DIR)

