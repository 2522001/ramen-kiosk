#pragma once

#include <string>
#include "menu.h"

class OrderList
{
private:
	Order** rmList;
	unsigned int count;

public:
	OrderList(void);
	~OrderList(void);

	Order* AddOrder(void);
	void DeleteOrder(unsigned int index);

	Order* GetOrder(unsigned int index);

	const unsigned int& Count = count;
};
