# Adapted from CS50x problem set source material.

# compiler to use
CC = clang

# flags to pass to compiler
CFLAGS = -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror

# executable name
EXE = sort

# header files
HDRS = header.h

# libraries
LIBS = -lrt

# source files
SRCS = sort.c algs.c helpers.c log.c statistics.c

# object files
OBJS = $(SRCS:.c=.o)

# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# dependencies
$(OBJS): $(HDRS) Makefile

# housekeeping
clean:
	rm -f core $(EXE) *.o
