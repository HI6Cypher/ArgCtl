CC := gcc
CFLAGS := -fPIC -std=c89 -O2 -Iinclude
SRC_DIR := src
OBJ_DIR := build
LIB_NAME := libargctl.so

src_files := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/utils/*.c)

obj_files := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(src_files))

$(LIB_NAME): $(obj_files)
	$(CC) -shared -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(obj_files) $(LIB_NAME)

