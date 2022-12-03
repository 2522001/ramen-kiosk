#include "cart.h"

OrderList::OrderList(void) : rmList(0), count(0)
{

}

OrderList::~OrderList(void)
{
	if (rmList) {
		for (unsigned int i = 0; i < count; i++) {
			if (rmList[i]) {
				delete rmList[i];
			}
		}
		delete[] rmList;
	}
}

Order* OrderList::AddOrder(void)
{
	Order** rmTemp = 0;

	rmTemp = new Order * [Count + 1];
	for (unsigned int i = 0; i < count; i++) {
		rmTemp[i] = rmList[i];
	}
	rmTemp[count] = new Order;
	count += 1;

	delete[] rmList;
	rmList = rmTemp;

	return rmList[Count - 1];
}

void OrderList::DeleteOrder(unsigned int index)
{
	Order** rmTemp = 0;

	if (index >= count) {
		return;
	}
	rmTemp = new Order * [count - 1];

	for (unsigned int i = 0; i < index; i++) {
		rmTemp[i] = rmList[i];
	}

	for (unsigned int i = index + 1; i < count; i++) {
		rmTemp[i - 1] = rmList[i];
	}

	delete rmList[index];
	count -= 1;

	delete[] rmList;
	rmList = rmTemp;
	return;
}

Order* OrderList::GetOrder(unsigned int index) {
	if (index >= count) {
		return 0;
	}
	return rmList[index];
}