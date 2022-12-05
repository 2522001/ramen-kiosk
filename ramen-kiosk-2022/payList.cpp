#include "payList.h"

PayList::PayList(void) : list(0), count(0)
{

}

PayList::~PayList(void)
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

Pay* PayList::AddPay(void)
{
	Pay** temp = 0;

	temp = new Pay * [Count + 1];
	for (unsigned int i = 0; i < count; i++) {
		temp[i] = list[i];
	}
	temp[count] = new Pay;
	count += 1;

	delete[] list;
	list = temp;

	return list[Count - 1];
}

void PayList::DeletePay(unsigned int index)
{
	Pay** temp = 0;

	if (index >= count) {
		return;
	}
	temp = new Pay * [count - 1];

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

Pay* PayList::GetPay(unsigned int index) {
	if (index >= count) {
		return 0;
	}
	return list[index];
}