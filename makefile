OPTS = -Wall -g
OTPS += -O

CC = gcc

all:
	$(MAKE) reverse wcat wgrep wunzip wzip

clean:
	./clean_binaries.sh

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
