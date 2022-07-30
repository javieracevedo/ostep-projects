TEST_TARGET = tests.c
SRCS = sort-text.c
TARGS = $(SRCS:.c:.o)
CC = gcc
OPTS = -Wall -g -O
LIBS = -I.

sort-text:
	$(CC) $(OPTS) $(SRCS) $(LIBS) -o sort-text.o

test:
	$(CC) $(OPTS) $(TEST_TARGET) $(LIBS) -o tests.o


clean:
	rm -f sort-text tests.o