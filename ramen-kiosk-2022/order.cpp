#include "order.h"

using namespace std;

Order::Order(void) : rmList(0), count(0)
{

}
Order::~Order(void)
{
	if (rmList) {
		for (unsigned int i = 0; i < count; i++) {
			if (rmList[i]) {
				delete rmList;
			}
		}
		delete[] rmList;
	}
}

void Order::AddObject(const Object& obj)
{
	Object** rmTemp = 0;

	for (unsigned int i = 0; i < count; i++) {
		if (rmList[i]->Name == obj.Name) {
			rmList[i]->EditCount(obj.Count);

			return;
		}
	}
	rmTemp = new Object * [count + 1];

	for (unsigned int i = 0; i < count; i++) {
		rmTemp[i] = rmList[i];
	}

	rmTemp[count] = new Object(obj);
	count += 1;

	delete[] rmList;
	rmList = rmTemp;

	return;
}

bool Order::DeleteObject(const Object& obj)
{
	unsigned int deleteId = 0;
	Object** rmTemp = 0;

	for (unsigned int i = 0; i < count; i++) {
		if (rmList[i]->Name == obj.Name) {
			if (rmList[i]->Count <= obj.Count) {
				deleteId = i;
				break;
			}
			else {
				rmList[i]->EditCount(-static_cast<int>(obj.Count));
				return false;
			}
		}
	}
	if (count > 1) {
		rmTemp = new Object * [count - 1];
	}
	for (unsigned int i = 0; i < deleteId; i++) {
		rmTemp[i] = rmList[i];
	}
	for (unsigned int i = deleteId + 1; i < count; i++) {
		rmTemp[i - 1] = rmList[i];
	}

	delete rmList[deleteId];
	count -= 1;

	delete[] rmList;
	rmList = rmTemp;

	return count == 0;
}

Object* Order::GetObject(unsigned int index) const {
	if (index >= count) {
		return 0;
	}
	return rmList[index];
}

Object* Order::GetObject(const string& name) const {
	for (unsigned int i = 0; i < count; i++) {
		if (rmList[i]->Name == name) {
			return rmList[i];
		}
	}
	return 0;
}

unsigned int Order::Calculate(void) const
{
	unsigned int sum = 0;

	for (unsigned int i = 0; i < count; i++) {
		sum += rmList[i]->Calculate();
	}
	return sum;
}