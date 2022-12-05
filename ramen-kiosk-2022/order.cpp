#include "order.h"

using namespace std;

Order::Order(void) : list(0), count(0)
{

}
Order::~Order(void)
{
	if (list) {
		for (unsigned int i = 0; i < count; i++) {
			if (list[i]) {
				delete list;
			}
		}
		delete[] list;
	}
}

void Order::AddOrderItem(const OrderItem& orderItem)
{
	OrderItem** temp = 0;

	for (unsigned int i = 0; i < count; i++) {
		if (list[i]->Name == orderItem.Name) {
			list[i]->EditCount(orderItem.Count);

			return;
		}
	}
	temp = new OrderItem * [count + 1];

	for (unsigned int i = 0; i < count; i++) {
		temp[i] = list[i];
	}

	temp[count] = new OrderItem(orderItem);
	count += 1;

	delete[] list;
	list = temp;

	return;
}

bool Order::DeleteOrderItem(const OrderItem& orderItem)
{
	unsigned int deleteId = 0;
	OrderItem** temp = 0;

	for (unsigned int i = 0; i < count; i++) {
		if (list[i]->Name == orderItem.Name) {
			if (list[i]->Count <= orderItem.Count) {
				deleteId = i;
				break;
			}
			else {
				list[i]->EditCount(-static_cast<int>(orderItem.Count));
				return false;
			}
		}
	}
	if (count > 1) {
		temp = new OrderItem * [count - 1];
	}
	for (unsigned int i = 0; i < deleteId; i++) {
		temp[i] = list[i];
	}
	for (unsigned int i = deleteId + 1; i < count; i++) {
		temp[i - 1] = list[i];
	}

	delete list[deleteId];
	count -= 1;

	delete[] list;
	list = temp;

	return count == 0;
}

OrderItem* Order::GetOrderItem(unsigned int index) const {
	if (index >= count) {
		return 0;
	}
	return list[index];
}

OrderItem* Order::GetOrderItem(const string& name) const {
	for (unsigned int i = 0; i < count; i++) {
		if (list[i]->Name == name) {
			return list[i];
		}
	}
	return 0;
}

unsigned int Order::Calculate(void) const
{
	unsigned int sum = 0;

	for (unsigned int i = 0; i < count; i++) {
		sum += list[i]->Calculate();
	}
	return sum;
}