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
	OrderItem(const OrderItem& copy); //������

	unsigned int EditCount(int count);
	unsigned int Calculate(void) const; //��ü ���� ���

	//�ܺ� ����
	const std::string& Name = name;
	const unsigned int& Price = price;
	const unsigned int& Count = count;

};