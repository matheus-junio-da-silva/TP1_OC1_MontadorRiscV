CC = gcc
AS = as
LD = ld
CFLAGS = -Wall -Wextra -g3

all: main

main: main.o soma.o
    $(CC) $(CFLAGS) -o $@ $^

main.o: main.c
    $(CC) $(CFLAGS) -c -o $@ $<

soma.o: soma.asm
    $(AS) -o $@ $<

clean:
    rm -f main main.o soma.o
