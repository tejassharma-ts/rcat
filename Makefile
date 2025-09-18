CC := gcc
CFLAGS := -Wall -Wextra -g
LDFLAGS := -lm
debug ?= 1
NAME := rcat
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
LIB_DIR := lib
BIN_DIR := bin

OBJS := $(patsubst %.c,%.o, $(wildcard $(SRC_DIR)/*.c) $(wildcard $(LIB_DIR)/**/*.c))

ifeq ($(debug), 1)
	CFLAGS := $(CFLAGS) -g -O0
else
	CFLAGS := $(CFLAGS) -Oz
endif

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BIN_DIR)/$@ $(patsubst %, build/%, $(OBJS))

$(OBJS): dir
	@mkdir -p $(BUILD_DIR)/$(@D)
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ -c $*.c

# Setup build and bin directories
dir:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

# Clean build and bin directories
clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: dir clean


# CC := gcc
# CFLAGS := -Wall -Wextra -g
# SRC := main.c token.c
# OBJ := $(SRC:.c=.o)
# TARGET := main
#
# $(TARGET): $(OBJ)
# 	$(CC) -o $@ $^
#
# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@
#
# .PHONY: clean
# clean:
# 	rm -f $(TARGET) $(OBJ)
#
