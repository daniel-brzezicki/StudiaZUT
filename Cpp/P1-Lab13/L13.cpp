#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Figura{
	char name[2];
	bool spawned=false;
};

struct Player {
	Figura figura[9] = {};
};

void ShowMap(char map[9][9]) {
	system("cls");
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			printf_s(" %c", map[y][x]);
		}
		printf("\n");
	}
}

void CreateMap(char map[9][9]) {
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			map[y][x] = { '.' };
			if (y == 0 && x == 0) {
				map[y][x] = 'X';
			}
			else if (y == 0) {
				map[y][x] = toupper('0' + x + 48);
			}
			else if (x == 0) {
				map[y][x] = '0' + y;
			}
		}
	}
}

void CreatePlayers(char map[9][9], Player *p) {

	for (int y = 1; y < 9; y++) {
		for (int x = 1; x < 9; x++) {
			if (y == 1) {
				map[y][x] = *p[0].figura[x].name;
			}
			else if (y == 2) {
				map[y][x] = *p[0].figura[0].name;
			}
			else if (y == 7) {
				map[y][x] = *p[1].figura[0].name;
			}
			else if (y == 8) {
				map[y][x] = *p[1].figura[x].name;
			}
		}
	}
}

void NameFigures(Player *p) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 9; j++) {
			switch (j) {
			case 0:
				if (i == 0) strcpy_s(p[i].figura[j].name, "p");
				else strcpy_s(p[i].figura[j].name, "P");
				break;
			case 1:
				if (i == 0) strcpy_s(p[i].figura[j].name, "w");
				else strcpy_s(p[i].figura[j].name, "W");
				break;
			case 2:
				if (i == 0) strcpy_s(p[i].figura[j].name, "s");
				else strcpy_s(p[i].figura[j].name, "S");
				break;
			case 3:
				if (i == 0) strcpy_s(p[i].figura[j].name, "g");
				else strcpy_s(p[i].figura[j].name, "G");
				break;
			case 4:
				if (i == 0) strcpy_s(p[i].figura[j].name, "h");
				else strcpy_s(p[i].figura[j].name, "H");
				break;
			case 5:
				if (i == 0) strcpy_s(p[i].figura[j].name, "k");
				else strcpy_s(p[i].figura[j].name, "K");
				break;
			case 6:
				if (i == 0) strcpy_s(p[i].figura[j].name, "g");
				else strcpy_s(p[i].figura[j].name, "G");
				break;
			case 7:
				if (i == 0) strcpy_s(p[i].figura[j].name, "s");
				else strcpy_s(p[i].figura[j].name, "S");
				break;
			case 8:
				if (i == 0) strcpy_s(p[i].figura[j].name, "w");
				else strcpy_s(p[i].figura[j].name, "W");
				break;
			}
		}
	}
}

int convert(char *ch) {
	int zmienna=0;

	switch (toupper(ch[0])) {
	case 'A':
		zmienna = 1;
		break;
	case 'B':
		zmienna = 2;
		break;
	case 'C':
		zmienna = 3;
		break;
	case 'D':
		zmienna = 4;
		break;
	case 'E':
		zmienna = 5;
		break;
	case 'F':
		zmienna = 6;
		break;
	case 'G':
		zmienna = 7;
		break;
	case 'H':
		zmienna = 8;
		break;
	}
	return zmienna;
}

int play(int which) {
	char ch[2];
	int zmienna;

	switch (which) {
	case 0:
		printf("Podaj wspolrzedna pionka: \n");
		printf("x: ");
		scanf_s(" %c", &ch);
		zmienna = convert(ch);

		break;
	case 1:
		printf("y: ");
		scanf_s("%d", &zmienna);
		break;
	case 2:
		printf("Podaj wspolrzedna celu: \n");
		printf("x: ");
		scanf_s(" %c", &ch);
		zmienna = convert(ch);
		break;
	case 3:
		printf("y: ");
		scanf_s("%d", &zmienna);
		break;
	}
	return zmienna;
}

bool isEmpty(char map[9][9],int target_x,int target_y) {
	char index[1];
	index[0] = map[target_y][target_x];
	if (index[0] != '.') {
		return false;
	}
	else {
		return true;
	}
}

void canMove(Player *p,char map[9][9],int pos_x, int pos_y, int target_x, int target_y) {
	char index[1];
	index[0] = map[pos_y][pos_x];
	if (map[pos_y][pos_x] != '.' && target_y != 0 && target_x != 0) {
		if (isEmpty(map, target_x, target_y)) {
			if (index[0] == 'p'|| index[0] == 'P') {
				if ((abs(target_x - pos_x) == 1 && target_y == pos_y) ||
					(abs(target_y - pos_y) == 1 && target_x == pos_x)){
					map[pos_y][pos_x] = '.';
					map[target_y][target_x] = *index;
				}
			}
			else if (index[0] == 'w' || index[0] == 'W') {
				if (target_y == pos_y || target_x == pos_x) {
					map[pos_y][pos_x] = '.';
					map[target_y][target_x] = *index;
				}
			}
			else if (index[0] == 'g' || index[0] == 'G') {
				if (abs(target_x - pos_x) == abs(target_y - pos_y)) {
					map[pos_y][pos_x] = '.';
					map[target_y][target_x] = *index;
				}
			}
			else if (index[0] == 's' || index[0] == 'S') {
				if ((abs(target_x - pos_x) == 2 && abs(target_y - pos_y) == 1) ||
					(abs(target_x - pos_x) == 1 && abs(target_y - pos_y) == 2)){
					map[pos_y][pos_x] = '.';
					map[target_y][target_x] = *index;
				}
			}
			else if (index[0] == 'h' || index[0] == 'H') {
				if ((abs(target_x - pos_x) == abs(target_y - pos_y)||
					(target_y == pos_y || target_x == pos_x))) {
					map[pos_y][pos_x] = '.';
					map[target_y][target_x] = *index;
				}
			}
		}
	}
	else if (map[pos_x][pos_y] == '.') {
		printf("Nie ma takiego pionka");
	}

}

int main()
{
	Player p[2];
	char plansza[9][9];
	int x = 0;
	int y = 0;
	int target_x = 0;
	int target_y = 0;


	NameFigures(p);

	CreateMap(plansza);
	CreatePlayers(plansza, p);
	ShowMap(plansza);

	while (1) {
		x = play(0);
		y = play(1);
		target_x = play(2);
		target_y = play(3);

		if ((x < 9 && x>0) &&
			(y < 9 && y>0) &&
			(target_x < 9 && target_x>0) &&
			(target_y < 9 && target_y>0)) {
			canMove(p, plansza, x, y, target_x, target_y);
		}

		ShowMap(plansza);
	}

	return 0;
}
