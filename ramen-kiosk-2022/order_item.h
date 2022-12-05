#pragma once

#include <string>
class OrderItem
{
private:
	std::string name;
	const unsigned int price;
	unsigned int count;

public:
	OrderItem(const std::string& name, unsigned int price, unsigned int count);
	OrderItem(const OrderItem& copy); //재참조

	unsigned int EditCount(int count);
	unsigned int Calculate(void) const; //전체 가격 계산

	//외부 참조
	const std::string& Name = name;
	const unsigned int& Price = price;
	const unsigned int& Count = count;

};