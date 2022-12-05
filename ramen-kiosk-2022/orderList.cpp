#include "orderList.h"

OrderList::OrderList(void) : list(0), count(0)
{

}

OrderList::~OrderList(void)
{
	if (list) {
		for (unsigned int i = 0; i < count; i++) {
			if (list[i]) {
				delete list[i];
			}
		}
		delete[] list;
	}
}

Order* OrderList::AddOrder(void)
{
	Order** temp = 0;

	temp = new Order * [Count + 1];
	for (unsigned int i = 0; i < count; i++) {
		temp[i] = list[i];
	}
	temp[count] = new Order;
	count += 1;

	delete[] list;
	list = temp;

	return list[Count - 1];
}

void OrderList::DeleteOrder(unsigned int index)
{
	Order** temp = 0;

	if (index >= count) {
		return;
	}
	temp = new Order * [count - 1];

	for (unsigned int i = 0; i < index; i++) {
		temp[i] = list[i];
	}

	for (unsigned int i = index + 1; i < count; i++) {
		temp[i - 1] = list[i];
	}

	delete list[index];
	count -= 1;

	delete[] list;
	list = temp;
	return;
}

Order* OrderList::GetOrder(unsigned int index) {
	if (index >= count) {
		return 0;
	}
	return list[index];
}