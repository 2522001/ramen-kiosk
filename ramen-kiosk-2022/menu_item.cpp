#include "menu_item.h"

Object::Object(const std::string& name, unsigned int price, unsigned int count) : name(name), price(price), count(count)
{

}

Object::Object(const Object& copy) : name(copy.name), price(copy.price), count(copy.count), Name(name), Price(price), Count(count)
{

}

unsigned int Object::EditCount(int count)
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

unsigned int Object::Calculate(void) const
{
	return price * count;
}