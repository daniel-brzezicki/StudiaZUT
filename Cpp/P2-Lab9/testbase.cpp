#include "pch.h"
#include <iostream>
#include <vector>
#include "BaseClass.h"


class OffensiveClass : public BaseClass
{
public:

	int damage;
	std::string shout;


	OffensiveClass(int health, std::string description, int damage, std::string shout);
	~OffensiveClass();

	int getDamage() const {
		return damage;
	}
};


OffensiveClass::OffensiveClass(int health, std::string description, int damage, std::string shout) :
	BaseClass::BaseClass(health, description) {
	this->health = health;
	this->description = description;
	this->damage = damage;
	this->shout = shout;
}

OffensiveClass::~OffensiveClass(){}

class PassiveClass : public BaseClass
{
private:

public:
	int resistance;
	int toAround;
	PassiveClass(int health, std::string description, int resistance, int toAround);
	~PassiveClass();

	int getDamage() const = 0;
};

int PassiveClass::getDamage() const {
	return 0;
}

PassiveClass::PassiveClass(int health, std::string description, int resistance, int toAround) :
	BaseClass::BaseClass(health, description) {
	this->health = health;
	this->description = description;
	this->resistance = resistance;
	this->toAround = toAround;
}

PassiveClass::~PassiveClass(){}

void CreateCharacters() {
	std::shared_ptr<BaseClass> player = std::make_shared<OffensiveClass>(20, "player", 5, "Shout!");

	std::vector<std::shared_ptr<BaseClass>> characters;


	for (int i = 0; i < 5; i++) {
		characters.push_back(std::make_shared<OffensiveClass>(2, "enemy", 1, "Shout!"));
	}


	for (auto character : characters) {
		player->dealDamage(character);
	}
}



int main()
{
	CreateCharacters();
}