SRCS = sort-text.c
TARG = sort-text.out
OBJS = $(SRCS:.c=.o)
CC = gcc
OPTS = -Wall -g -O0

$(TARG): $(OBJS)
	$(CC) $(SRCS) -o $(TARG) $(OPTS)

clean:
	rm -f $(TARGS)

depend:
	makedepend $(SRCS)