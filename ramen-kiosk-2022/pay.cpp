#include "pay.h"

using namespace std;

Pay::Pay(void) : paymentList(0), count(0)
{

}
Pay::~Pay(void)
{
	if (paymentList) {
		for (unsigned int i = 0; i < count; i++) {
			if (paymentList[i]) {
				delete paymentList;
			}
		}
		delete[] paymentList;
	}
}

void Pay::AddPayment(const Payment& obj)
{
	Payment** pmTemp = 0;

	pmTemp = new Payment * [count + 1];

	for (unsigned int i = 0; i < count; i++) {
		pmTemp[i] = paymentList[i];
	}

	pmTemp[count] = new Payment(obj);
	count += 1;

	delete[] paymentList;
	paymentList = pmTemp;

	return;
}

bool Pay::DeletePayment(const Payment& obj)
{
	unsigned int deleteId = 0;
	Payment** pmTemp = 0;

	for (unsigned int i = 0; i < count; i++) {
		if (paymentList[i]->Name == obj.Name) {
				deleteId = i;
				break;
			}
		}
	if (count > 1) {
		pmTemp = new Payment * [count - 1];
	}
	for (unsigned int i = 0; i < deleteId; i++) {
		pmTemp[i] = paymentList[i];
	}
	for (unsigned int i = deleteId + 1; i < count; i++) {
		pmTemp[i - 1] = paymentList[i];
	}

	delete paymentList[deleteId];
	count -= 1;

	delete[] paymentList;
	paymentList = pmTemp;

	return count == 0;
}

Payment* Pay::GetPayment(unsigned int index) const {
	if (index >= count) {
		return 0;
	}
	return paymentList[index];
}

Payment* Pay::GetPayment(const string& name) const {
	for (unsigned int i = 0; i < count; i++) {
		if (paymentList[i]->Name == name) {
			return paymentList[i];
		}
	}
	return 0;
}