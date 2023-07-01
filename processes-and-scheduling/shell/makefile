SRCS = wish.c cli_parser.c built_in_commands.c system_commands.c error_handling.c
TARG = wish
OBJS = $(SRCS:.c=.o)
CC = gcc
OPTS = -Wall -ggdb -O0

$(TARG): $(OBJS)
	$(CC) $(SRCS) -o $(TARG) $(OPTS)

clean:
	rm -f $(TARG)

depend:
	makedepend  $(SRCS)