SRCS = 	initial-utilities/reverse/reverse.c \
				initial-utilities/wcat/wcat.c \
				initial-utilities/wgrep/wgrep.c \
				initial-utilities/wunzip/wunzip.c \
				initial-utilities/wzip/wzip.c

OBJS =	$(SRCS:.c=.o)
TARGS = $(SRCS:.c=.out)

OPTS = -Wall -g
OTPS += -O

CC = gcc

all:
	$(MAKE) reverse wcat wgrep wunzip wzip

clean:
	rm -f ${OBJS} ${TARGS}
	$(MAKE) reverse_clean 

reverse:
	cd initial-utilities/reverse && make
reverse_clean:
	cd initial-utilities/reverse && make clean

wcat:
	cd initial-utilities/wcat && make
wcat_clean:
	cd initial-utilities/reverse && make clean

wgrep:
	cd initial-utilities/wgrep && make
wgrep_clean:
	cd initial-utilities/wgrep && make clean

wunzip:
	cd initial-utilities/wunzip && make
wunzip_clean:
	cd initial-utilities/wunzip && make

wzip:
	cd initial-utilities/wzip && make
wzip_clean:
	cd initial-utilities/wzip && make clean

