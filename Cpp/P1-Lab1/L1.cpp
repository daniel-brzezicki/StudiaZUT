#include "pch.h"
#include <iostream>
#include <math.h>

float pi = 3.14159265359;

float add(float a, float b) {
	return a + b;
}
float min(float a, float b) {
	return a - b;
}
float mul(float a, float b) {
	return a * b;
}
float div(float a, float b) {
	return a / b;
}
float m_sin(float a) {
	return sin(a * (pi / 180.0));
}
float m_cos(float a) {
	return cos(a * (pi / 180.0));
}


float getvalue() {
	float value;
	scanf_s("%f", &value);

	return value;
}

char getch() {
	char znak;
	scanf_s(" %c", &znak);

	return znak;
}


int main()
{
	float first_num, second_num, wynik;
	char sign;
	int inf = 0;

	printf_s("Podaj liczbe: ");
	first_num = getvalue();

	while (inf == 0) {
		printf_s("Podaj znak: ");
		sign = getch();
		if ((sign == 's') || (sign == 'c')) {
			switch (sign) {
			case 's':
				first_num = m_sin(first_num);
				break;
			case 'c':
				first_num = m_cos(first_num);
				break;
			}
		}
		else {
			printf_s("Podaj liczbe: ");
			second_num = getvalue();
			switch (sign) {
			case '+':
				first_num = add(first_num, second_num);
				break;
			case '-':
				first_num = min(first_num, second_num);
				break;
			case '*':
				first_num = mul(first_num, second_num);
				break;
			case '/':
				first_num = div(first_num, second_num);
				break;
			}
		}
		printf_s("%f\n", first_num);
	}
}
