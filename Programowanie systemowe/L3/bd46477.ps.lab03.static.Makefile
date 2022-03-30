zad1: zad1_lib.o zad1.o
	gcc -o zad1 zad1_lib.o zad1.o
zad1_lib.o: zad1_lib.c
	gcc -c zad1_lib.c
zad1.o: zad1.c
	gcc -c zad1.c

