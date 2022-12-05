#pragma once

#include <string>
#include "order_item.h"

class Order
{
private:
	OrderItem** list;
	unsigned int count;

public:
	Order(void);
	~Order(void);

	void AddOrderItem(const OrderItem& orderItem);
	bool DeleteOrderItem(const OrderItem& orderItem);

	OrderItem* GetOrderItem(unsigned int index) const;
	OrderItem* GetOrderItem(const std::string& name) const;

	unsigned int Calculate(void) const;

	//외부 참조
	const unsigned int& Count = count;
};

typedef Order MenuItem;