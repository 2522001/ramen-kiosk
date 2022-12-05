#pragma once

#include <string>
#include "Order.h"

class OrderList
{
private:
	Order** list;
	unsigned int count;

public:
	OrderList(void);
	~OrderList(void);

	Order* AddOrder(void);
	void DeleteOrder(unsigned int index);

	Order* GetOrder(unsigned int index);

	const unsigned int& Count = count;
};
