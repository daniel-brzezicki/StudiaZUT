#include "pch.h"
#include <iostream>


void t_1() {
	printf_s("    #   \n");
	printf_s("   ###  \n");
	printf_s("  ##### \n");
	printf_s(" #######\n");
}

void t_2() {
	int wysokosc;
	scanf_s("%d", &wysokosc);
	for (int i = 0; i < wysokosc; i++) {
		for (int spacje = wysokosc - i; spacje > 0; spacje--) {
			printf_s(" ");
		}
		printf_s("#");
		for (int choinka = 0; choinka < i; choinka++) {
			printf_s("##");
		}
		printf_s("\n");
	}
}


int main(int argc, char* argv[])
{
	t_1();
	t_2();
	int wysokosc = atoi(argv[1]);
	//printf_s("%d\n", wysokosc);


	for (int i = 0; i < wysokosc; i++) {
		for (int spacje = wysokosc - i; spacje > 0; spacje--) {
			printf_s(" ");
		}
		printf_s("#");
		for (int choinka = 0; choinka < i; choinka++) {
			printf_s("##");
		}
		printf_s("\n");
	}

	system("pause");
}
