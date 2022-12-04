#pragma once

#include <string>
class Payment
{
private:
	std::string name;

public:
	Payment(const std::string& name);
	Payment(const Payment& copy);

	const std::string& Name = name;
};