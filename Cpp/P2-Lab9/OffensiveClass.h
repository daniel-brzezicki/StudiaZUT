#pragma once
#ifndef OFFENSIVECLASS_H
#define OFFENSIVECLASS_H

#include <string>
#include "BaseClass.h"
#include "PassiveClass.h"

class OffensiveClass : virtual public BaseClass
{
public:

	int damage;
	std::string shout;


	OffensiveClass(int health, std::string description, int damage, std::string shout);
	~OffensiveClass();

	virtual int getDamage();
};

#endif

