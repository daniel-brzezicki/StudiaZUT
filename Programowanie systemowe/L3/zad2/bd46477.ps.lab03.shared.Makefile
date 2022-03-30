CFLAGS=-Wall -g

all: zad2_lib.so zad2.o

zad2_lib.so: zad2_lib.c
	gcc $(CFLAGS) -fPIC -shared -o $@ $^

zad2.o: zad2.c
	gcc $(CFLAGS) -o $@ $^ -ldl


