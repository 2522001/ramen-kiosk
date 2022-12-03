#include "pay_list.h"

PayList::PayList(void) : paymentList(0), count(0)
{

}

PayList::~PayList(void)
{
	if (paymentList) {
		for (unsigned int i = 0; i < count; i++) {
			if (paymentList[i]) {
				delete paymentList[i];
			}
		}
		delete[] paymentList;
	}
}

Pay* PayList::AddPay(void)
{
	Pay** paymentTemp = 0;

	paymentTemp = new Pay * [Count + 1];
	for (unsigned int i = 0; i < count; i++) {
		paymentTemp[i] = paymentList[i];
	}
	paymentTemp[count] = new Pay;
	count += 1;

	delete[] paymentList;
	paymentList = paymentTemp;

	return paymentList[Count - 1];
}

void PayList::DeletePay(unsigned int index)
{
	Pay** paymentTemp = 0;

	if (index >= count) {
		return;
	}
	paymentTemp = new Pay * [count - 1];

	for (unsigned int i = 0; i < index; i++) {
		paymentTemp[i] = paymentList[i];
	}

	for (unsigned int i = index + 1; i < count; i++) {
		paymentTemp[i - 1] = paymentList[i];
	}

	delete paymentList[index];
	count -= 1;

	delete[] paymentList;
	paymentList = paymentTemp;
	return;
}

Pay* PayList::GetPay(unsigned int index) {
	if (index >= count) {
		return 0;
	}
	return paymentList[index];
}