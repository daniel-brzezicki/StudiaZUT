#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#define SIZE 10

int show_values(int *t,int elements) {
	//int elements = SIZE;
	for (int i = 0; i < elements; i++) {
		printf_s("%d. %d\n", i + 1, t[i]);
	}

	return 0;
}

int add(int *t, int elements) {
	//int elements = SIZE;
	int sum = 0;
	for (int i = 0; i < elements; i++) {
		sum += t[i];
	}

	return sum;
}

int average(int *t, int elements) {
	//int elements = SIZE;
	return add(t, elements) / elements;
}

int min(int *t, int elements) {
	//int elements = SIZE;
	int min = t[0];
	for (int i = 0; i < elements; i++) {
		if (min > t[i]) {
			min = t[i];
		}
	}

	return min;
}

int max(int *t, int elements) {
	//int elements = SIZE;
	int max = t[0];
	for (int i = 0; i < elements; i++) {
		if (max < t[i]) {
			max = t[i];
		}
	}

	return max;
}

int *add_tabs(int *t, int *t2, int elements) {
	//int elements = SIZE;
	int *tr = (int *)malloc(sizeof(int)*elements);

	for (int i = 0; i < elements; i++) {
		tr[i] = t[i] + t2[i];
	}

	return tr;
}

int *get_data(int elements) {
	int *tab = (int *)malloc(sizeof(int)*elements);
	int liczba;
	for (int i = 0; i < elements; i++) {
		tab[i] = rand();
	}
	return tab;
}



int main()
{
	srand(time(NULL));

	int elements = 10;
	int * t1 = get_data(elements);
	int * t2 = get_data(elements);

	show_values(t1, elements);
	//show_values(t2, elements);
	printf_s("Dodawanie: %d\n", add(t1, elements));
	printf_s("Srednia: %d\n", average(t1, elements));
	printf_s("Min: %d\n", min(t1, elements));
	printf_s("Max: %d\n", max(t1, elements));

	show_values(add_tabs(t1, t2, elements),elements);
	free(t1);
	free(t2);
}
