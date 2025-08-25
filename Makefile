# GCC compiler
CC = gcc

# Compiler flags
# Wall + Wextra: all warnings + extra warnings
# std=c11: use C 11
# Iinclude: I directory, basically where to look for include files
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Final compiled binary
TARGET = ${FINAL_BINARY}

# Fetch all .c files in src as names
SRCS = $(wildcard src/*.c)

# For all .c files fetched from c, rename them to .o files placed in build
OBJS = $(patsubst src/%.c, build/%.o, $(SRCS))


# Default make, runs the rule for target we defined prior
# At the top as the default target
all: $(TARGET)


# If build directory called as prereq, create dir if doenst exist
build:
	mkdir -p build


# If pattern matched like in OBJS and used as a prereq
#
# - first check if it exists OR src .c file is newer 
#   if so, run the build rule since prereq
#
# - then compile into objects NO linking hence .o files
#   $< is the FIRST prereq so src/%.c NOT build
#   $@ is the target so build/%.o
build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@


# Rule for compiling the target
#
# - target: prerequisites
# 
# - Check if prereqs are newer than target, if so continue
#   gcc (flags) outputFlag finalBinary objectFiles
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)


clean:
	rm -rf build $(TARGET)
