PRJ_NAME := etc
GIT_VER  := $(shell git describe --abbrev=8 --dirty --always --tags)
TARGET   := $(PRJ_NAME) #-$(GIT_VER)
CXX      := gcc
CXXFLAGS := -O0 -Wall # -Wextra -Werror -pedantic-errors -v
LDFLAGS  := -L/usr/lib -lstdc++ -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/obj
APP_DIR  := $(BUILD)/bin

#include directories
INCLUDE  := -Isrc/logger/
INCLUDE  += -Isrc/serial/

USER_FLAGS := -DSERIAL_TEST_INCLUDED 
USER_FLAGS += -DLOG_TEST_INCLUDED

#sources directories
SRC      :=                       \
	$(wildcard src/*.c)           \
	$(wildcard src/logger/*.c)    \
	$(wildcard src/serial/*.c)    \
#   $(wildcard src/xxx/*.cpp) \


OBJECTS := $(SRC:%.c=$(OBJ_DIR)/%.o)

all: CXXFLAGS += $(USER_FLAGS)
all: build $(APP_DIR)/$(TARGET)
	-@echo $(PRJ_NAME)-$(GIT_VER)
	-@echo Release Done
	
$(OBJ_DIR)/%.o: %.c
	-@echo obj dir
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	-@echo app dir
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

#all: CXXFLAGS += $(USER_FLAGS)
#all: build $(APP_DIR)/$(TARGET)
#	-@echo all
#	-@echo $(PRJ_NAME)-$(GIT_VER)
#	-@echo Release Done

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)
	@echo complete actions och

debug: CXXFLAGS += -g -DDEBUG 
debug: all

release: 
release: all

clean:
	-@rm -rf $(BUILD)
#	-@rm -rf $(OBJ_DIR)/*
#	-@rm -rf $(APP_DIR)/*
	-@echo Clean Done

.PHONY: all build clean debug release
	