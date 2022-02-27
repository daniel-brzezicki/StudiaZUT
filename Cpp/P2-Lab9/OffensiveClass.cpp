#include "pch.h"
#include "OffensiveClass.h"
#include "BaseClass.h"


OffensiveClass::OffensiveClass(int health, std::string description, int damage, std::string shout) :
	BaseClass::BaseClass(health, description) {
	this->health = health;
	this->description = description;
	this->damage = damage;
	this->shout = shout;
}

OffensiveClass::~OffensiveClass()
{

}

int OffensiveClass::getDamage()
{
	return damage;
}


