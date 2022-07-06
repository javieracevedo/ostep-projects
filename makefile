OBJS =	initial-utilities/reverse/reverse.o \
				initial-utilities/wcat/wcat.o \
				initial-utilities/wgrep/wgrep.o \
				initial-utilities/wunzip/wunzip.o \
				initial-utilities/wzip/wzip.o

TARGS = 	initial-utilities/reverse/reverse.out \
					initial-utilities/wcat/wcat.out \
					initial-utilities/wgrep/wgrep.out \
					initial-utilities/wunzip/wunzip.out \
					initial-utilities/wzip/wzip.out

OPTS = -Wall -g
OTPS += -O

CC = gcc

all:
	$(MAKE) reverse wcat wgrep wunzip wzip

clean:
	rm  ${OBJS} ${TARGS}

reverse:
	cd initial-utilities/reverse && make

wcat:
	cd initial-utilities/wcat && make

wgrep:
	cd initial-utilities/wgrep && make

wunzip:
	cd initial-utilities/wunzip && make

wzip:
	cd initial-utilities/wzip && make
