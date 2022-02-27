// 2_l11.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <memory>
#include <iomanip>
#include <ctime>
#include <windows.h>

class Tree {
public:
	virtual void DoThing(int count, int width) = 0;
};

class BranchEmpty : public Tree {
public:
	void DoThing(int count, int width);
};

class BranchWithBaubles : public Tree {
public:
	void DoThing(int count, int width);
};

class BranchWithLights : public Tree {
public:
	void DoThing(int count, int width);
};

void BranchEmpty::DoThing(int count, int width) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	std::cout << std::setfill(' ') << std::setw(width - count+1) << ' ';
	std::cout << std::setfill('*');
	for (int i = 0; i < (count * 2 - 1); i++) {
			std::cout << '*';
	}
	std::cout << std::setfill('*');
	std::cout << "\n";
}

void BranchWithBaubles::DoThing(int count, int width) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	std::cout << std::setfill(' ') << std::setw(width - count + 1) << ' ';
	std::cout << std::setfill('*');
	for (int i = 0; i < (count * 2 - 1); i++) {
		int r = std::rand() % 15 + 1;
		if ((i % r == r - 1)) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), r);
			std::cout << '@';
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			std::cout << '*';
		}
	}
	std::cout << std::setfill('*');
	std::cout << "\n";
}

void BranchWithLights::DoThing(int count, int width) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	std::cout << std::setfill(' ') << std::setw(width - count + 1) << ' ';
	std::cout << std::setfill('*');
	for (int i = 0; i < (count * 2 - 1); i++) {
		int r = std::rand() % 15 + 1;
		if ((i % r == r - 1)) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			std::cout << 'i';
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			std::cout << '*';
		}
	}
	std::cout << std::setfill('*');
	std::cout << "\n";
}


int main()
{
	srand(time(NULL));
	
	std::unique_ptr<Tree> strategy = std::make_unique<BranchEmpty>();
	int width = 10;

	for (int i = 0; i <= width; i++) {
		strategy->DoThing(i, width);
	}

	strategy = std::make_unique<BranchWithBaubles>();
	for (int i = 0; i <= width; i++) {
		strategy->DoThing(i, width);
	}

	strategy = std::make_unique<BranchWithLights>();
	for (int i = 0; i <= width; i++) {
		strategy->DoThing(i, width);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}
