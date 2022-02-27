#include "pch.h"
#include <iostream>
#include <string>

class Number {
public:
	std::string liczba;

	Number(std::string liczba = "") {
		this->liczba = liczba;
	}

	~Number() {}

	std::string convert() {
		bool hasDot = false;
		int counter = 0;
		int zeros;

		switch (liczba.at(liczba.length() - 1)) {
		case 'M':
			zeros = 6;
			break;
		case 'B':
			zeros = 9;
			break;
		case 'T':
			zeros = 12;
			break;
		case 'a':
			zeros = 15;
			liczba.pop_back();
			break;
		case 'i':
			zeros = 18;
			liczba.pop_back();
			break;
		case 'x':
			zeros = 21;
			liczba.pop_back();
			break;
		case 'p':
			zeros = 24;
			liczba.pop_back();
			break;
		case 'c':
			zeros = 27;
			liczba.pop_back();
			break;
		}


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
		return liczba;
	}
};


int main()
{
	Number xMil("4M");
	Number xBil("4.5B");
	std::cout << xMil.convert() << std::endl;
	std::cout << xBil.convert() << std::endl;
}