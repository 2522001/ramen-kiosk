#pragma once

#include <string>
#include "menu_item.h"

class Order
{
private:
	Object** rmList;
	unsigned int count;

public:
	Order(void);
	~Order(void);

	void AddObject(const Object& obj);
	bool DeleteObject(const Object& obj);

	Object* GetObject(unsigned int index) const;
	Object* GetObject(const std::string& name) const;

	unsigned int Calculate(void) const;

	//외부 참조
	const unsigned int& Count = count;
};

typedef Order MenuItem;