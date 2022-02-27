#include "pch.h"
#include "PassiveClass.h"
#include "BaseClass.h"



PassiveClass::PassiveClass(int health, std::string description, int resistance, int toAround) :
	BaseClass::BaseClass(health, description) {
	this->health = health;
	this->description = description;
	this->resistance = resistance;
	this->toAround = toAround;
}

PassiveClass::~PassiveClass()
{
}

