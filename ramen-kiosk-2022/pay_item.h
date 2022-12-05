#pragma once

#include <string>
class PayItem
{
private:
	std::string name;

public:
	PayItem(const std::string& name);
	PayItem(const PayItem& copy);

	const std::string& Name = name;
};