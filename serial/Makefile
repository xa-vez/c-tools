TARGET   := serial
CXX      := gcc
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror #-v
LDFLAGS  := -L/usr/lib #-lstdc++ -lm
BUILD    := ./build
OBJ_DIR  := $(BUILD)/obj
APP_DIR  := $(BUILD)/bin
INCLUDE  := -Isrc/serial/
SRC      :=                      \
	$(wildcard src/*.c)          \
    $(wildcard src/serial/*.c) \
#   $(wildcard src/module2/*.cpp) \


OBJECTS := $(SRC:%.c=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)
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
                        