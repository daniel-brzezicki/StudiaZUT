#include "pch.h"
#include <iostream>
#include <string>
#include <ctime>


class Item {
private:	
	std::string itemName;
public:

	Item(int value) {
		switch (value) {
		case 0:
			itemName = "Key";
			break;
		case 1:
			itemName = "Sword";
			break;
		case 2:
			itemName = "Gold";
			break;
		default:
			itemName = "Unsigned Item";
		}
	}

	std::string Name() {
		return itemName;
	}

};

class Room
{
private:

public:	
	std::string description = "#";
	Room *n;
	Room *e;
	Room *s;
	Room *w;
	Item *i;
	int x;
	int y;

	Room(int x, int y) {
		this->x = x;
		this->y = y;
	}

	Room(Room *r) {
		this->n = r->n;
		this->e = r->e;
		this->s = r->s;
		this->w = r->w;
		this->i = r->i;
		this->x = r->x;
		this->y = r->y;
	}

	~Room(){}

	std::string ShowDescription() {
		return description;
	}

	void SetNeighbour(Room *rooms[3][8], int y, int x) {
		SetNeighbourNorth(rooms[y - 1][x]);
		SetNeighbourEast(rooms[y][x + 1]);
		SetNeighbourSouth(rooms[y + 1][x]);
		SetNeighbourWest(rooms[y][x - 1]);
	}

	void SetNeighbourNorth(Room *n) {
		if (n != nullptr)
			this->n = n;
	}
	void SetNeighbourSouth(Room *e) {
		if (e != nullptr)
			this->e = e;
	}
	void SetNeighbourEast(Room *s) {
		if (s != nullptr)
			this->s = s;
	}
	void SetNeighbourWest(Room *w) {
		if (w != nullptr)
			this->w = w;
	}

	bool CanGo(char path) {
		switch (path) {
		case 'n':
			if (this->n != nullptr)
				return true;
			else
				return false;
			break;
		case 'e':
			if (this->e != nullptr)
				return true;
			else
				return false;
			break;
		case 's':
			if (this->s != nullptr)
				return true;
			else
				return false;
			break;
		case 'w':
			if (this->w != nullptr)
				return true;
			else
				return false;
			break;
		}
	}

	Room getDirection(char path) {
		switch (path) {
		case 'n':
			if (this->n != nullptr)
				return *n;
			break;
		case 'e':
			if (this->e != nullptr)
				return *e;
			break;
		case 's':
			if (this->s != nullptr)
				return *s;
			break;
		case 'w':
			if (this->w != nullptr)
				return *w;
			break;
		}
	}

	void SpawnItem() {
		int r = rand() % 100;
		if (r <= 25) {
			i = new Item(rand() % 2);
		}
	}

	bool hasItem() {
		if (i != nullptr) {
			std::cout << "You have found " << i->Name();
			return true;
		}
		else {
			return false;
		}
	}

	void ShowCoords(){
		std::cout << "coords: (" << x << "," << y << ")" << std::endl;
	}

};

void CreateMap(Room *rooms[3][8]) {
	for(int x = 0; x < 3; x++) {
		for (int y = 0; y < 8; y++) {

			rooms[x][y] = new Room(y, x);
		}
	}

	delete rooms[0][2]; rooms[0][2] = nullptr;
	delete rooms[0][4]; rooms[0][4] = nullptr;
	delete rooms[1][0]; rooms[1][0] = nullptr;
	delete rooms[1][6]; rooms[1][6] = nullptr;
	delete rooms[2][2]; rooms[2][2] = nullptr;
	delete rooms[2][4]; rooms[2][4] = nullptr;

	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 8; x++) {
			if (rooms[y][x] != nullptr) {
				rooms[y][x]->SetNeighbour(rooms,y,x);
				rooms[y][x]->SpawnItem();
				std::cout << "#";
			}
			else {
				std::cout << "X";
			}
		}
		std::cout << std::endl;
	}
}


void Go(Room *rooms[3][8]) {
	Room *currRoom = rooms[0][0];
	int steps = 0;

	std::string path = "essweneesnnseeneewwsse";

	for (auto direction : path) {
		if (currRoom->CanGo(direction)) {
			*currRoom = currRoom->getDirection(direction);
			currRoom->ShowCoords();
			steps++;
		}
	}
}

int main()
{
	srand(time(0));
	Room *rooms[3][8];
	CreateMap(rooms);
	Go(rooms);
}
 