# Makefile template for shared library

CC = g++ # C++ compiler
# CFLAGS = -std=c++11 -Wall -Wextra -O2 -g # C++ flags
CFLAGS = -std=c++11 # C++ flags
BUILD = build
RM = rm -f  # rm command

# .PHONY: main
# all: ${TARGET_LIB}

clean:
	$(RM) *.o

word_count: word_count.cpp
	$(CC) $(CFLAGS) $^ -o $@ && time ./word_count

merge: merge.cpp
	$(CC) $(CFLAGS) $^ -o $@ && time ./merge

build_index: build_index.cpp helper.o
	$(CC) $(CFLAGS) $^ -o $@
	# $(CC) $(CFLAGS) $^ -o $@ && time ./build_index

read_test: read_test.cpp helper.o
	$(CC) $(CFLAGS) $^ -o $@

helper.o: helper.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

# main: main.cpp helper.o
# 	$(CC) $(CFLAGS) $^ -o $@

# $(OBJS): $(SRCS)
# 	$(CC) $(CFLAGS) -c $^ -o $@

# $(TARGET_LIB): $(OBJS)
# 	$(CC) $^ -o $@

# .PHONY: clean
# clean:
# 	-${RM} ${TARGET_LIB} ${OBJS} $(TARGET_LIB)

# TARGET_LIB = libhelper.so # target lib

# SRCS = helper.cpp # source files
# OBJS = $(SRCS:.cpp=.o)