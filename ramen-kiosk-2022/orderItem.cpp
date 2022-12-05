#include "orderItem.h"

OrderItem::OrderItem(const std::string& name, unsigned int price, unsigned int count) : name(name), price(price), count(count)
{

}

OrderItem::OrderItem(const OrderItem& copy) : name(copy.name), price(copy.price), count(copy.count), Name(name), Price(price), Count(count)
{

}

unsigned int OrderItem::EditCount(int count)
{
	unsigned int prev = 0;

	prev = this->count;

	if (static_cast<int>(Count) + count < 0) {
		this->count = 0;
		return prev;
	}
	prev = this->count;

	this->count += count;

	return prev;
}

unsigned int OrderItem::Calculate(void) const
{
	return price * count;
}