#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fileWrite()
{
	int random_num;

	for (int i = 0; i < 10; i++)
	{
		char fileName[100];
		sprintf_s(fileName, "outfile %d.txt ", i);
		FILE* outputFile;
		fopen_s(&outputFile, fileName, "w");
		if (outputFile != NULL) {
			for (int j = 0; j < 100; j++) {
				random_num = rand() % 11;
				fprintf_s(outputFile, "%d\n", random_num);
			}
		}
		fclose(outputFile);
	}
}


void fileRead(int* t) {


	int t_counters[10][11] = {};
	int t_counters_iar[10][11] = {};

	for (int i = 0; i < 10; i++)
	{

		char fileName[100];
		sprintf_s(fileName, "outfile %d.txt ", i);
		FILE* outputFile;
		fopen_s(&outputFile, fileName, "r");
		if (outputFile != NULL) {
			int last_value = -1;
			int actual_length = 1;
			for (int j = 0; j < 100; j++) {
				fscanf_s(outputFile, "%d", &t[j]);
				printf_s("%d. %d\n", j + 1, t[j]);
				t_counters[i][t[j]]++;
				if (last_value == t[j]) {
					actual_length++;
				}
				else
				{
					actual_length = 1;
					last_value = t[j];
				}
				if (t_counters_iar[i][t[j]] < actual_length)
					t_counters_iar[i][t[j]] = actual_length;
			}
		}
		fclose(outputFile);
	}


	char fileName[100];
	sprintf_s(fileName, "results.txt ");
	FILE *outputFile;
	fopen_s(&outputFile, fileName, "w");
	fprintf_s(outputFile, "############# -         Liczba wystapien         -   Najdluzsze wystapienie z rzedu\n");
	fprintf_s(outputFile, "Nazwa pliku   -  0  1  2  3  4  5  6  7  8  9 10 -  0  1  2  3  4  5  6  7  8  9 10\n");
	fprintf_s(outputFile, "-----------------------------------------------------------------------------------\n");
	if (outputFile != NULL) {

		for (int k = 0; k < 10; k++) {
			fprintf_s(outputFile, "outfile %d.txt - ", k);
			for (int l = 0; l < 11; l++) {
				if (t_counters[k][l] >= 10) {
					fprintf_s(outputFile, "%d ", t_counters[k][l]);
				}
				else {
					fprintf_s(outputFile, " %d ", t_counters[k][l]);
				}

			}
			fprintf_s(outputFile, "- ");
			for (int m = 0; m < 11; m++) {
				if (t_counters_iar[k][m] >= 10) {
					fprintf_s(outputFile, "%d ", t_counters_iar[k][m]);
				}
				else {
					fprintf_s(outputFile, " %d ", t_counters_iar[k][m]);
				}
			}
			fprintf_s(outputFile, "\n");
		}
	}
	fclose(outputFile);

}



int main()
{
	int* tab;
	tab = (int *)malloc(sizeof(int) * 100);

	srand(time(NULL));

	fileWrite();
	fileRead(tab);

	free(tab);
}
