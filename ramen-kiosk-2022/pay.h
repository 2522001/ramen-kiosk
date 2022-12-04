#pragma once

#include <string>
#include "pay_item.h"

class Pay
{
private:
	Payment** paymentList;
	unsigned int count;

public:
	Pay(void);
	~Pay(void);

	void AddPayment(const Payment& obj);
	bool DeletePayment(const Payment& obj);

	Payment* GetPayment(unsigned int index) const;
	Payment* GetPayment(const std::string& name) const;

	const unsigned int& Count = count;
};

typedef Pay PayPreset;