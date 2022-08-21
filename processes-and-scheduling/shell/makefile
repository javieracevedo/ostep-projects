SRCS = wish.c
TARG = wish.out
OBJS = $(SRCS:.c=.o)
CC = gcc
OPTS = -Wall -ggdb -O0

$(TARG): $(OBJS)
	$(CC) $(SRCS) -o $(TARG) $(OPTS)

clean:
	rm -f $(TARG)

depend:
	makedepend  $(SRCS)