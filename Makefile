BASE_SRC := aes_common.c

SOFTWARE_DIR := software
NEON_DIR := armv8
BUILD_SOFT := build-soft
BUILD_NEON := build-neon

NAMES := aes_key.c aes_func.c aes_dec.c aes_enc.c
SOFT_SRCS := $(BASE_SRC) $(addprefix $(SOFTWARE_DIR)/,$(NAMES))
NEON_SRCS := $(BASE_SRC) $(addprefix $(NEON_DIR)/,$(NAMES))
SOFT_OBJS := $(BASE_SRC) $(addprefix $(BUILD_SOFT)/,$(NAMES))
NEON_OBJS := $(BASE_SRC) $(addprefix $(BUILD_NEON)/,$(NAMES))
SOFT_OBJS := $(patsubst %.c,%.o,$(SOFT_OBJS))
NEON_OBJS := $(patsubst %.c,%.o,$(NEON_OBJS))

CC := aarch64-linux-gnu-gcc

INC_FLAGS := -I. -I..
C_FLAGS := $(INC_FLAGS) -std=c99

SOFT_FLAGS := -march=armv8-a
NEON_FLAGS := -march=armv8-a+crc+crypto


all: soft neon

# software implementation
soft: $(BUILD_SOFT)/aes_soft.out

$(BUILD_SOFT)/%.o: $(SOFTWARE_DIR)/%.c
	$(CC) -c $(C_FLAGS) $(SOFT_FLAGS) $^ -o $@

$(BUILD_SOFT)/aes_soft.out: $(SOFT_OBJS)
	$(CC) $(C_FLAGS) $(SOFT_FLAGS) $^ -o $@

neon: $(BUILD_NEON)/aes_neon.out

$(BUILD_NEON)/aes_neon.out: $(NEON_OBJS)
	@echo $(CC) $(NEON_FLAGS) $^ -o $@

.PHONY: run-neon run-soft

run-soft:
	./$(BUILD_SOFT)/aes_soft.out
