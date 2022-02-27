#pragma once
#ifndef PASSIVECLASS_H
#define PASSIVECLASS_H

#include <string>
#include "BaseClass.h"

class PassiveClass : virtual public BaseClass
{
private:

public:
	int resistance;
	int toAround;
	PassiveClass(int health, std::string description, int resistance, int toAround);
	~PassiveClass();
};

#endif

