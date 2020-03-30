SRC_DIR := .
BUILD_DIR := build

NAMES := aes.c test.c
OBJS := $(addprefix $(BUILD_DIR)/,$(NAMES))
OBJS := $(patsubst %.c,%.o,$(OBJS))

CC := aarch64-linux-gnu-gcc

INC_FLAGS := -I.
C_FLAGS := $(INC_FLAGS) -g3 -std=gnu99

ARCH_FLAGS := -march=armv8-a
# ARCH_FLAGS := -march=armv8-a+crc+crypto


# software implementation
all: $(BUILD_DIR)/aes.out

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(C_FLAGS) $(ARCH_FLAGS) $^ -o $@

$(BUILD_DIR)/aes.out: $(OBJS)
	$(CC) $(C_FLAGS) $(ARCH_FLAGS) $^ -o $@


# run the stuff
.PHONY: run clean

run:
	./$(BUILD_DIR)/aes.out

clean:
	@rm -f ./$(BUILD_DIR)/aes.out
	@rm -f ./$(BUILD_DIR)/*.o
