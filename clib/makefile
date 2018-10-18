# Makefile template for shared library

CC = g++ # C++ compiler
CFLAGS = -std=c++11 -fPIC -Wall -Wextra -O2 -g # C flags
LDFLAGS = -shared  # linking flags
RM = rm -f  # rm command
TARGET_LIB = libhelper.so # target lib

SRCS = helper.cpp # source files
OBJS = $(SRCS:.cpp=.o)

.PHONY: all
all: ${TARGET_LIB}

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $^ -o $@

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} $^ -o $@

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(TARGET_LIB)

# SHELL = /bin/sh
# CC    = g++
# FLAGS        = -std=c++11 -c # -std=gnu99 -Iinclude
# CFLAGS       = -fPIC -Wl #-pedantic -Wall -Wextra -ggdb3
# LDFLAGS      = -shared
# TARGET  = libhelper.so
# SOURCES = $(shell echo clib/*.cpp)
# # HEADERS = $(shell echo include/*.h)
# OBJECTS = $(SOURCES:.cpp=.o)

# # PREFIX = $(DESTDIR)/usr/local
# # BINDIR = $(PREFIX)/bin

# all: $(TARGET)
# clean: 

# $(TARGET): $(OBJECTS)
# 	$(CC) $(FLAGS) $(CFLAGS) -o $(TARGET) $(OBJECTS)
