TEST_TARGET = tests.c
SRCS = $(TEST_TARGET) sort-text.c
TARGS = $(SRCS:.c:.o)

CC = gcc
OPTS = -Wall -g -O
LIBS = -I.

test:
	$(CC) $(OPTS) $(TEST_TARGET) $(LIBS) -o tests.o