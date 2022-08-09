SRCS = wish.c

TARG = wish.out

CC = gcc

OPTS = -Wall
OTPS += -O0

OBJS = $(SRCS:.c=.o)

$(TARG): $(OBJS)
	$(CC) -o $(TARG) $(OPTS) $(OBJS) 

clean:
	rm -f $(OBJS) $(TARG)

depend:
	makedepend  $(SRCS)