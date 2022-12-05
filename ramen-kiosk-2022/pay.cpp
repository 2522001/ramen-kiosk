#include "pay.h"

using namespace std;

Pay::Pay(void) : list(0), count(0)
{

}
Pay::~Pay(void)
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

void Pay::AddPayItem(const PayItem& payitem)
{
	PayItem** temp = 0;

	temp = new PayItem * [count + 1];

	for (unsigned int i = 0; i < count; i++) {
		temp[i] = list[i];
	}

	temp[count] = new PayItem(payitem);
	count += 1;

	delete[] list;
	list = temp;

	return;
}

bool Pay::DeletePayItem(const PayItem& payitem)
{
	unsigned int deleteId = 0;
	PayItem** temp = 0;

	for (unsigned int i = 0; i < count; i++) {
		if (list[i]->Name == payitem.Name) {
				deleteId = i;
				break;
			}
		}
	if (count > 1) {
		temp = new PayItem * [count - 1];
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

PayItem* Pay::GetPayItem(unsigned int index) const {
	if (index >= count) {
		return 0;
	}
	return list[index];
}

PayItem* Pay::GetPayItem(const string& name) const {
	for (unsigned int i = 0; i < count; i++) {
		if (list[i]->Name == name) {
			return list[i];
		}
	}
	return 0;
}