﻿#include "pch.h"
#include <iostream>
#include <string>

class number {
public:
	void convert(int zeros, std::string &liczba);
};

void number::convert(int zeros, std::string &liczba) {
	bool hasDot = false;
	int counter = 0;

	liczba.pop_back();
	for (int i = liczba.length() - 1; i >= 0; i--) {
		if (liczba.at(i) != '.') {
			counter++;
		}
		else {
			hasDot = true;
			break;
		}
	}

	if (!hasDot) {
		counter = 0;
	}
	else {
		liczba.erase(liczba.length() - (counter + 1), 1);
	}

	for (int i = 0; i < zeros - counter; i++) {
		liczba.push_back('0');
	}
}



void input_num(std::string liczba) {
	number num;

	switch (liczba.at(liczba.length() - 1)) {
	case 'M':
		num.convert(6, liczba);
		break;
	case 'B':
		num.convert(9, liczba);
		break;
	case 'T':
		num.convert(12, liczba);
		break;
	case 'a':
		liczba.pop_back();
		num.convert(15, liczba);
		break;
	case 'i':
		liczba.pop_back();
		num.convert(18, liczba);
		break;
	case 'x':
		liczba.pop_back();
		num.convert(21, liczba);
		break;
	case 'p':
		liczba.pop_back();
		num.convert(24, liczba);
		break;
	case 'c':
		liczba.pop_back();
		num.convert(27, liczba);
		break;
	}

	std::cout << liczba << std::endl;
}


int main()
{
	input_num("4M");
	input_num("4.5M");
	input_num("5B");
	input_num("5.555Oc");
}