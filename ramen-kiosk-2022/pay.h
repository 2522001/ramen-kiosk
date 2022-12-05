#pragma once

#include <string>
#include "payItem.h"

class Pay
{
private:
	PayItem** list;
	unsigned int count;

public:
	Pay(void);
	~Pay(void);

	void AddPayItem(const PayItem& payitem);
	bool DeletePayItem(const PayItem& payitem);

	PayItem* GetPayItem(unsigned int index) const;
	PayItem* GetPayItem(const std::string& name) const;

	const unsigned int& Count = count;
};

typedef Pay PayPreset;