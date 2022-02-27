#include "pch.h"
#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <time.h>


class Player {
public:
	std::string name;
	std::string lastName;
	std::string height;
	std::string stats[5] = { "glowki","strzelanie","szybkosc","podawanie","rzuty" };

	Player(std::string name = "", std::string lastName = "", std::string height = "0") {
		this->name = name;
		this->lastName = lastName;
		this->height = height;
	}


	void modify(std::string name, std::string last_name, std::string height, std::string s0, std::string s1, std::string s2, std::string s3, std::string s4) {
		this->name = name;
		this->lastName = last_name;
		this->height = height;
		this->stats[0] = s0;
		this->stats[1] = s1;
		this->stats[2] = s2;
		this->stats[3] = s3;
		this->stats[4] = s4;
	}

	void modifyStats(std::string stats[5]) {
		for (int i = 0; i < std::size(this->stats); i++) {
			this->stats[i] = stats[i];
		}
	}

	std::string toString() {
		return(name + ";" + lastName + ";" + height + ";" + stats[0] + ";" + stats[1] + ";" + stats[2] + ";" + stats[3] + ";" + stats[4]);
	}

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

	void load() {
		Team t;
		std::string playerInfo;

		std::fstream inputFile("file.txt", std::ios::in | std::ios::out | std::ios::app);

		if (!inputFile.is_open()) {
			throw std::exception("Can't read file.txt");
		}

		std::string lineFromFile;
		int playerInArray=0;
		while(getline(inputFile, lineFromFile)){
			playerInfo = lineToPlayer(lineFromFile,playerInArray);
			playerInArray++;
		}
		inputFile.close();
	}

	std::string lineToPlayer(std::string line, int playerInArray) {
		std::string temp;
		int whichWord = 0;

		while (whichWord != 7) {
			for (int j = 0; j < line.length(); j++) {
				if (line.at(j) != ';') {
					temp.push_back(line.at(j));
				}
				else {
					if (whichWord == 0)p[playerInArray].name = temp;
					else if (whichWord == 1)p[playerInArray].lastName = temp;
					else if (whichWord == 2)p[playerInArray].height = temp;
					else if (whichWord == 3)p[playerInArray].stats[0] = temp;
					else if (whichWord == 4)p[playerInArray].stats[1] = temp;
					else if (whichWord == 5)p[playerInArray].stats[2] = temp;
					else if (whichWord == 6)p[playerInArray].stats[3] = temp;
					else if (whichWord == 7)p[playerInArray].stats[4] = temp;

					temp.clear();
					whichWord++;
				}
			}
		}


		return temp;
	}

	void save(Team t) {
		std::string n = getFileName();

		std::ofstream outputFile(getFileName());
		if (!outputFile.is_open()) throw std::exception("Can't write file");
		for (int i = 0; i<std::size(t.p); i++){
			outputFile<<t.p[i].toString()<<std::endl;
		}
		outputFile.close();
	}

	std::string getFileName() {
		time_t t = time(0);
		struct tm now;
		localtime_s(&now, &t);

		std::string time = '_' + std::to_string(now.tm_year + 1900) + '-' + std::to_string(now.tm_mon + 1) + '-' + std::to_string(now.tm_mday) + '_' + std::to_string(now.tm_hour) + '_' + std::to_string(now.tm_min) + '_' + std::to_string(now.tm_sec) + ".txt";
		std::string fileName = "druzyna";
		return fileName + time;
	}
};




Player RandomPlayer() {
	Player *p[10];
	p[0] = new Player("Robert", "Lewandowski", "184");
	p[1] = new Player("Mariusz", "Pudzianowski", "180");
	p[2] = new Player("Adam", "Kownacki", "191");
	p[3] = new Player("Adam", "Malysz", "170");
	p[4] = new Player("Kamil", "Stoch", "176");
	p[5] = new Player("Robert", "Kubica", "185");
	p[6] = new Player("Magda", "Gessler", "168");
	p[7] = new Player("Marcin", "Gortat", "211");
	p[8] = new Player("Wojciech", "Szczesny", "195");
	p[9] = new Player("Jan", "Blachowicz", "188");


	int random = rand() % 10;

	return *p[random];
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
	Team t4 = t[1];

	t4.load();
	t4.save(t4);
}