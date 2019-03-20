RESULT ?= ble-dialog-semiconductor

# user definitions
DEFINES =                       \
    -DBLUEZ_VERSION_MAJOR=5     \
    -DBLUEZ_VERSION_MINOR=50    \
    -DGATTLIB_FORCE_DBUS=TRUE 

# include directories
INCLUDES  :=                                      \
	-I../utils/gattlib/include/                   \
	-I../utils/gattlib/bluez/                     \
	-I../utils/gattlib/bluez/bluez5/              \
	-I../utils/gattlib/bluez/bluez5/lib/          \
	-I../utils/gattlib/dbus/                      \
	-I../utils/gattlib/build/dbus/                \
	-I../../../../common/                         \
	-I../../../../tools/etc/src/date-time/        \
	-I../../../../tools/etc/src/serial/ 

# asm sources
ASM_SOURCES =

# c sources
C_SOURCES :=                                      \
	../src/main.c                                 \
	../utils/gattlib/gattlib_common.c             \
	../utils/gattlib/dbus/gattlib.c               \
	../utils/gattlib/build/dbus/org-bluez-adaptater1.c \
	../utils/gattlib/build/dbus/org-bluez-battery1.c \
	../utils/gattlib/build/dbus/org-bluez-device1.c \
	../utils/gattlib/build/dbus/org-bluez-gattcharacteristic1.c  \
	../utils/gattlib/build/dbus/org-bluez-gattservice1.c  \
	../utils/gattlib/dbus/bluez5/lib/uuid.c       \
	../../../../common/debug.c                    \
    ../../../../tools/etc/src/date-time/date-time.c \
    ../../../../tools/etc/src/serial/serial.c     

# headers
HEADERS :=                                        \
	../utils/gattlib/build/dbus/org-bluez-adaptater1.h \
	../utils/gattlib/build/dbus/org-bluez-battery1.h \
	../utils/gattlib/build/dbus/org-bluez-device1.h \
	../utils/gattlib/build/dbus/org-bluez-gattcharacteristic1.h \
	../utils/gattlib/build/dbus/org-bluez-gattservice1.h \
	../../../../common/debug_settings.h           \
	../../../../common/debug.h                    \
	../../../../common/types.h                    \
	../../../../tools/etc/src/date-time/date-time.h \
	../../../../tools/etc/src/serial/serial.h     

ASM_OBJECTS = $(patsubst %.S, %.o, $(ASM_SOURCES))

C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))

OUTPUT_DIR = output
OBJ_DIR = $(OUTPUT_DIR)/obj

LINKER_SCRIPT =

CFLAGS += -fno-common -Wall -Os -g3 -ffunction-sections -fdata-sections -Wl,-M=$(OUTPUT_DIR)/$(RESULT).map
#CFLAGS += -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
CFLAGS += $(DEFINES)
CFLAGS += $(INCLUDES)


#DEPENDENCIES +=
DEPENDENCIES += -lbluetooth -lcurses `pkg-config --libs glib-2.0 --libs gio-unix-2.0 --cflags gio-unix-2.0 --cflags glib-2.0`

#CROSS_COMPILE ?= arm-none-eabi-
CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJDUMP = $(CROSS_COMPILE)objdump
OBJCOPY = $(CROSS_COMPILE)objcopy
SIZE = $(CROSS_COMPILE)size

THIS_MAKEFILE := $(lastword $(MAKEFILE_LIST))

#################################################
#################################################
all: build dump copy usage
#################################################
#################################################


#################################################
#####              RULES                     ####
#################################################
# create executable
build: $(RESULT) usage	

# create .lst
dump: build $(RESULT).lst

# create .bin
copy: build $(RESULT).bin

# dump memory usage
usage: size

# clean rule
clean:
#	rm -f $(RESULT).elf
#	rm -f $(RESULT).bin
#	rm -f $(RESULT).lst
#	rm -f $(RESULT).map
	rm -rf $(OUTPUT_DIR)
	
	

$(ASM_OBJECTS): | $(OBJ_DIR)

$(C_OBJECTS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $@



# @echo 1 
$(RESULT): \
	$(ASM_OBJECTS) $(C_OBJECTS) $(HEADERS) $(LINKER_SCRIPT) $(THIS_MAKEFILE)
	$(CC) $(addprefix $(OBJ_DIR)/, $(notdir $(ASM_OBJECTS))) $(addprefix $(OBJ_DIR)/, $(notdir $(C_OBJECTS))) $(CFLAGS) $(LFLAGS) $(DEPENDENCIES) -o $(OUTPUT_DIR)/$@ 

#	@echo 1.1 
%.o: %.c $(HEADERS) $(THIS_MAKEFILE)
	$(CC) $(DEPENDENCIES) $(CFLAGS) -c $< -o $(addprefix $(OBJ_DIR)/, $(notdir $@))
#	@echo 1.2 
%.o: %.S $(HEADERS) $(THIS_MAKEFILE)
	$(CC) $(DEPENDENCIES) $(CFLAGS) -c $< -o $(addprefix $(OBJ_DIR)/, $(notdir $@))



#echo 3
%.lst: % 	
	$(OBJDUMP) -x -S $(OUTPUT_DIR)/$(RESULT) > $(OUTPUT_DIR)/$@



#@echo 4
%.bin: %
	$(OBJCOPY) -O binary $(OUTPUT_DIR)/$< $(OUTPUT_DIR)/$@



# size rule
#@echo 5
size: 
	size $(OUTPUT_DIR)/$(RESULT)

