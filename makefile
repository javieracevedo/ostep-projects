OPTS = -Wall -g
OTPS += -O
CC = gcc

ROOT_DIRECTORY = ./initial-utilities
DIRS := ${shell find ./initial-utilities -maxdepth 1}

all:
	$(MAKE) reverse wcat wgrep wunzip wzip

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


.PHONY : clean
clean:
	$(foreach dir, ${DIRS}, rm -fv $(dir)/*.out)
	$(foreach dir, ${DIRS}, rm -fv $(dir)/*.o)
