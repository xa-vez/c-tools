GIT_VER  :=  $(shell git describe --abbrev=8 --dirty --always --tags)
TARGET   := serial-$(GIT_VER)
CXX      := gcc
CXXFLAGS :=  -Wall # -Wextra -Werror -pedantic-errors -v
LDFLAGS  := -L/usr/lib #-lstdc++ -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/obj
APP_DIR  := $(BUILD)/bin

#include directories
INCLUDE  := -Isrc/serial/

#sources directories
SRC      :=                       \
	$(wildcard src/*.c)           \
    $(wildcard src/serial/*.c)    \
#   $(wildcard src/module2/*.cpp) \


OBJECTS := $(SRC:%.c=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)
	-@echo serial-$(GIT_VER)
	-@echo Release Done
	
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O0
release: all

clean:
	-@rm -rf $(OBJ_DIR)/*
	-@rm -rf $(APP_DIR)/*
	-@echo Clean Done
                        