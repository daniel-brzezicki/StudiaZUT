#pragma once
#ifndef BASECLASS_H
#define BASECLASS_H
#include <string>

class BaseClass
{
public:
	int health;
	std::string description;
	void dealDamage(std::shared_ptr<BaseClass> &enemy);
	virtual int getDamage() const = 0;
	virtual std::string GetDescription();


	BaseClass(int health, std::string description);
	~BaseClass();
	int GetHP();

};

#endif

