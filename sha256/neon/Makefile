SRC_DIR := .
BUILD_DIR := build
TARGET := sha256.out

NAMES := sha256.c sha256_test.c
OBJS := $(addprefix $(BUILD_DIR)/,$(NAMES))
OBJS := $(patsubst %.c,%.o,$(OBJS))

CC := aarch64-linux-gnu-gcc

INC_FLAGS := -I.
C_FLAGS := $(INC_FLAGS) -g3 -std=gnu99

ARCH_FLAGS := -march=armv8-a+crc+crypto


# neon implementation
all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(C_FLAGS) $(ARCH_FLAGS) $^ -o $@

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(C_FLAGS) $(ARCH_FLAGS) $^ -o $@


# run the stuff
.PHONY: run clean

run:
	./$(BUILD_DIR)/$(TARGET)

clean:
	@rm -f ./$(BUILD_DIR)/$(TARGET)
	@rm -f ./$(BUILD_DIR)/*.o
