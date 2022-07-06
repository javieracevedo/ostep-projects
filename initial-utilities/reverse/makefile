SRCS = reverse.c

TARG = reverse.out

CC = gcc

OPTS = -Wall -g
OTPS += -O

OBJS = $(SRCS:.c=.o)

$(TARG): $(OBJS)
	$(CC) -o $(TARG) $(OPTS) $(OBJS) 

clean:
	rm -f $(OBJS) $(TARG)

depend:
	makedepend  $(SRCS)