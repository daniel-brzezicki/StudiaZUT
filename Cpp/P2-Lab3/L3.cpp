#include "pch.h"
#include <iostream>
#include <string>
#include <time.h>


class Player {
private:
	std::string name;
	std::string lastName;
	int height;
	std::string stats[5] = { "glowki","strzelanie","szybkosc","podawanie","rzuty" };
public:
	Player(std::string name = "", std::string lastName = "", int height = 0) {
		this->name = name;
		this->lastName = lastName;
		this->height = height;
	}


	//Dzialajace, lecz aktualnie niepotrzebne
	/*void modify(std::string name, std::string last_name, int height, std::string stats[5]) {
		this->name = name;
		this->lastName = last_name;
		this->height = height;
		for (int i = 0; i < std::size(this->stats); i++) {
			this->stats[i] = stats[i];
		}
	}

	void modifyStats(std::string stats[5]) {
		for (int i = 0; i < std::size(this->stats); i++) {
			this->stats[i] = stats[i];
		}
	}*/

	void show_player() {
		std::cout << "Imie: " << name << std::endl;
		std::cout << "Nazwisko: " << lastName << std::endl;
		std::cout << "Wzrost: " << height << std::endl;
		for (int i = 0; i < std::size(stats); i++) {
			std::cout << "Statistic " << i << ":" << stats[i] << std::endl;
		}
		std::cout << std::endl;
	}
};

class Team {
public:
	Player p[5];

	Team() {
	}

	Team(Team &t) {
		for (int i = 0; i < std::size(p); i++) {
			this->p[i] = t.p[i];
		}
	}


	void show_team() {
		for (int i = 0; i < std::size(p); i++) {
			if (i == 0) std::cout << "==========================" << std::endl;
			std::cout << "Player nr: " << i + 1 << std::endl;
			p[i].show_player();
		}
	}
};

Player RandomPlayer() {
	Player p[10];
	p[0] = *new Player("Robert", "Lewandowski", 184);
	p[1] = *new Player("Mariusz", "Pudzianowski", 180);
	p[2] = *new Player("Adam", "Kownacki", 191);
	p[3] = *new Player("Adam", "Malysz", 170);
	p[4] = *new Player("Kamil", "Stoch", 176);
	p[5] = *new Player("Robert", "Kubica", 185);
	p[6] = *new Player("Magda", "Gessler", 168);
	p[7] = *new Player("Marcin", "Gortat", 211);
	p[8] = *new Player("Wojciech", "Szczesny", 195);
	p[9] = *new Player("Jan", "Blachowicz", 188);


	int random = rand() % 10;

	return p[random];
}


int main() {
	srand(time(NULL));
	Team t[2];

	for (int i = 0; i < std::size(t); i++) {
		for (int j = 0; j < std::size(t->p); j++) {
			t[i].p[j] = RandomPlayer();
		}
		t[i].show_team();
	}

	Team t3(t[1]);

	t3.show_team();

}
