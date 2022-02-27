#include "pch.h"
#include "BaseClass.h"


BaseClass::BaseClass(int health, std::string description)
{
	this->health = health;
	this->description = description;
}

BaseClass::~BaseClass()
{
}

int BaseClass::GetHP()
{
	return this->health;
}

std::string BaseClass::GetDescription()
{
	return this->description;
}

void BaseClass::dealDamage(std::shared_ptr<BaseClass> &enemy)
{
	enemy->health -= getDamage();
	this->health -= enemy->getDamage();
	if (enemy->health <= 0) {
		//delete &enemy;
	}
	else if (this->health <= 0) {
		//delete this;
	}
}
