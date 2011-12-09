CC=gcc
CFLAGS=-O2 -Wall -W -pedantic

all: testavl

avl_demo:
$(CC) test_avl.c avltree.c -o test_avl

clean:
@rm test_avl

.PHONY: clean