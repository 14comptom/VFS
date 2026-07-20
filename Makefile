# =====================================================
# Compiler settings
# =====================================================

CC = gcc
CFLAGS = -std=c99 -D_DEFAULT_SOURCE -Wall -Wextra -pedantic -Iinclude

# =====================================================
# Output program name (OS Aware)
# =====================================================

ifeq ($(OS),Windows_NT)
    TARGET = vfs.exe
else
    TARGET = vfs
endif

# =====================================================
# Source files (Auto-discovery)
# =====================================================

SRCS := $(wildcard src/*.c) \
        $(wildcard src/*/*.c) \
        $(wildcard src/*/*/*.c)

# =====================================================
# Build Rules
# =====================================================

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# =====================================================
# Run Rule
# =====================================================

run: all
ifeq ($(OS),Windows_NT)
	.\$(TARGET)
else
	./$(TARGET)
endif

# =====================================================
# Clean Rule
# =====================================================

clean:
ifeq ($(OS),Windows_NT)
	if exist $(TARGET) del /Q /F $(TARGET)
else
	rm -f $(TARGET)
endif

# =====================================================
# Phony targets
# =====================================================

.PHONY: all run clean