#include <iostream>
#include "kiosk_handler.h"

OrderCategory::OrderCategory(const MenuItem& item, OrderList* pOrderList, const PayPreset& payItem, PayList* pPayList, RevenueManager* pRevManager) : bPrint(true), item(item), pOrderList(pOrderList), payItem(payItem), pPayList(pPayList), pRevManager(pRevManager)
{
	// ��� ���� �ʱ�ȭ
	mode = 0; // default: ������ ���
	is_paid = 1; // default: ���� �Ϸ�
}

bool OrderCategory::Run(void) {
	using namespace std;

	int menu = 0; // �Է� ��ȣ (������ ������ҵ�)
	mode = 0;

	cout << "---------------------------" << endl;
	cout << "<�����̳� ��鰡��>" << endl;
	cout << "1. ���ο� �ֹ�" << endl;
	cout << "2. �ֹ� Ȯ��" << endl;
	cout << "3. �ֹ� ����" << endl;
	cout << "4. ����" << endl;
	cout << "5. Ű����ũ ����" << endl;
	cout << "---------------------------" << endl << endl;

	cout << "> ������ ��ȣ�� �Է��ϼ���: ";
	cin >> menu;
	system("cls");
	switch (menu) {
	// case 0:
		// bPrint = true;
		// break;
	case 1:
		AddOrder();
		break;
	case 2:
		PrintOrder();
		break;
	case 3:
		EditOrder();
		break;
	case 4:
		AddPayment();
		break;
	case 5:
		Settings();
		break;
	default:
		cout << "�߸� �Է��ϼ̽��ϴ�." << endl << "�޴��� �ٽ� ����մϴ�." << endl;
		bPrint = true;
		break;

	}
	return true;
}

bool OrderCategory::Settings(void) {
	using namespace std;

	int menu = 0; // �Է� ��ȣ (������ ������ҵ�)
	mode = 1; // ������ ���

	cout << "---------------------------" << endl;
	cout << "<������ ���>" << endl;
	cout << "�ϴ� ��ȣ�� ������ �� �Է� �� ������ ��带 �����մϴ�." << endl;
	cout << "1. ��ü �ֹ� ���� Ȯ��" << endl;
	cout << "2. �ֹ� ���� ����" << endl;
	cout << "3. ����" << endl;
	cout << "4. Ű����ũ ����" << endl;
	cout << "---------------------------" << endl << endl;


	cout << "> (������ ���) ������ ��ȣ�� �Է��ϼ���: ";
	cin >> menu;
	switch (menu) {
	case 1:
		PrintOrder();
		break;
	case 2:
		EditOrder();
		break;
	case 3:
		cout << endl
			<< "���� �� ������� " << pRevManager->Today << "���Դϴ�." << endl << endl;
		break;
	case 4:
		exit(0);
	default:
		cout << endl << "Ȩ ȭ������ ���ư��ϴ�." << endl << endl;
		break;
	}
	return true;
}

void OrderCategory::AddOrder(void) {
	using namespace std;

	string objName;
	string objSpicy;
	string objCooked;

	unsigned int objCount = 0;
	Object* pObj = 0;
	Object* pEditObj = 0;
	Order* pOrder = 0;
	Order* pEditing = 0;

	string new_order;

	system("cls");

	cout << "-------------------------------------------------------------------" << endl <<
		"<�޴���>" << endl << endl
		<< "[��ǰ]" << endl
		<< "1. ��� ����: �Ϲݶ��, ���κζ��, �����, ���ζ��, ġ����" << endl
		<< "2. �ʱ� ����: ���ʰ�, �⺻, ���ʰ�" << endl
		<< "3. ���� ����: �����ϰ�, �⺻, ������" << endl << endl

		<< "[����]" << endl
		<< "1. �ݶ�" << endl
		<< "2. ���̴�" << endl << endl

		<< "[����]" << endl
		<< "1. �ܹ���" << endl
		<< "2. ��ġ" << endl << endl

		<< "[��Ʈ�޴�]" << endl
		<< "1. ��Ʈ �޴� 1��: ��� 2�� + ���� 1�� + ���� 1��" << endl
		<< "2. ��Ʈ �޴� 1��: ��� 1�� + ���� 1�� + ���� 1��" << endl

		<< "-------------------------------------------------------------------" << endl << endl
		<< "-->�Է����� : �޴� �̸�" << endl;

	cout << "(0�� �Է��ϸ� �޴� �ֹ��� �����մϴ�.)" << endl << endl;

	if (is_paid == 0) {
		cout << "�������� ���� �ֹ��� �ֽ��ϴ�. (���� �ֹ��� ������ 3���� �����Ͽ� �������ּ���.)" << endl
			<< "���� �ֹ��� �����ϰ� ���� �ֹ��Ͻðڽ��ϱ�? ��/�ƴϿ�: ";
		cin >> new_order;
		if (new_order == "��") {
			// ���� �ʿ� ������ ���� �ֹ� ����
			pEditing = pOrderList->GetOrder(pOrderList->Count - 1);
			if (pEditing) {
				// order �� ��� object ����
				for (unsigned int i = 0; i < pEditing->Count; i++) {
					pEditObj = pEditing->GetObject(i);
					pEditObj = new Object(pEditObj->Name, pEditObj->Price, pEditObj->Count);
				}
				if (pEditing->DeleteObject(*pEditObj)) { // object�� ��� ���� �Ǿ� order�� ����ٸ�
					pOrderList->DeleteOrder(pOrderList->Count - 1); // �ش� �ֹ� �ֹ�����Ʈ���� ����

					delete pEditObj;
				}
			}
			cout << "���� �Ϸ�" << endl;

			is_paid = 1;
		}
		else { // �ϴ� '��' �̿ܿ� �ƹ��ų� �Է� �� �۵��ϵ��� �� (���� ���� ó�� �ʿ�)
			cout << "Ȩ ȭ������ ���ư��ϴ�." << endl;
			return;
		}
	}

	if (is_paid == 1) {
		pOrder = pOrderList->AddOrder();
		while (true) {
			cout << "> �ֹ��� �޴��� �Է��ϼ���: ";
			cin >> objName;

			if (objName == "0") {
				break;
			}

			pObj = item.GetObject(objName);
			if (pObj == 0) {
				cout << "�ش� �޴��� �����ϴ�." << endl;
				continue;
			}


			cout << "> �ش� �޴��� � �ֹ��Ͻðڽ��ϱ�?: ";
			cin >> objCount;

			if (objCount == 0) {
				break;
			}

			pObj = new Object(objName, pObj->Price, objCount);

			pOrder->AddObject(*pObj);

			// ��� �ֹ��� ��쿡�� �ʱ�, ���� ���� ���� 
			if (objName == "�Ϲݶ��" || objName == "���κζ��" || objName == "�����" || objName == "���ζ��" || objName == "ġ����") {
				cout << "> �ʱ������� �Է��ϼ���: ";
				cin >> objSpicy;

				if (objSpicy == "0") {
					break;
				}

				pObj = item.GetObject(objSpicy);
				if (pObj == 0) {
					cout << "�ش� �޴��� �����ϴ�." << endl;
					continue;
				}

				pObj = new Object(objSpicy, 0, 0);
				pOrder->AddObject(*pObj);

				cout << "> ���������� �Է��ϼ���: ";
				cin >> objCooked;

				if (objCooked == "0") {
					break;
				}

				pObj = item.GetObject(objCooked);
				if (pObj == 0) {
					cout << "�ش� �޴��� �����ϴ�." << endl;
					continue;
				}

				pObj = new Object(objCooked, 0, 0);

				pOrder->AddObject(*pObj);

			}

			delete pObj;

			cout << endl << "��ٱ��Ͽ� �ֹ��� �߰��Ǿ����ϴ�." << endl << endl;
		}
		if (pOrder->Count == 0) {
			cout << "�ֹ��� �߰����� �ʾҽ��ϴ�." << endl;
			pOrderList->DeleteOrder(pOrderList->Count - 1);

			return;
		}
		is_paid = 0; // ���ο� �ֹ��� �߰��Ǿ����Ƿ� ���� �ʿ� ���·� ��ȯ
		cout << endl << "Ȩ ȭ������ ���ư��ϴ�." << endl << endl;
		return;
	}
}

void OrderCategory::PrintOrder(void) {
	using namespace std;

	Order* pOrder = 0;
	Object* pObj = 0;
	unsigned int sum = 0;
	unsigned int index = 0;

	if (mode == 0) { // ������ ���: ���� �ʿ� ������ ���� �ֱ� �ֹ� ���
		cout << endl << "������ �ֹ��� Ȯ���մϴ�." << endl << endl;
		if (is_paid == 1) {
			cout << "�ֹ��� �����ϴ�." << endl << endl;
			return;
		}
		else {
			pOrder = pOrderList->GetOrder((pOrderList->Count) - 1);
			cout << "<��ٱ���>" << endl;
			cout << "-------------------------------------------------------------------" << endl << endl;
			cout << "[�ֹ���ȣ " << (pOrderList->Count) - 1 << "��] " << endl << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << "(�ֹ�����)" << endl << endl;
			for (unsigned int j = 0; j < pOrder->Count; j++) {
				pObj = pOrder->GetObject(j);
				cout << " ->     " << pObj->Name << "   " << pObj->Count << "��        " << pObj->Calculate() << "��" << endl;
				sum += pObj->Calculate();
			}
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << " - �� ���� �ݾ�: " << sum << "��." << endl << endl;
			sum = 0;
		}
	} else { // ������ ���: ���� �Ϸ� ������ ��� �ֹ� ����Ʈ ���
		if (is_paid == 0) {
			index = pOrderList->Count - 1; // ���� �ֱ� �ֹ��� ���� �ʿ� ������ ��� �ش� �ֹ� ���� ���
		}
		else {
			index = pOrderList->Count;
		}
		cout << endl << "��ü �ֹ� ������ Ȯ���մϴ�." << endl << endl;
		if (pOrderList->Count == 0) {
			cout << "�ֹ��� �����ϴ�." << endl << endl;
			return;
		}
		for (unsigned int i = 0; i < index; i++) {
			pOrder = pOrderList->GetOrder(i);

			cout << "<��ٱ���>" << endl;
			cout << "-------------------------------------------------------------------" << endl << endl;
			cout << "[�ֹ���ȣ " << i << "��] " << endl << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << "(�ֹ�����)" << endl << endl;
			//cout << "        (�޴�)               (����)      (�ݾ�)   " << endl;
			for (unsigned int j = 0; j < pOrder->Count; j++) {
				pObj = pOrder->GetObject(j);
				cout << " ->     " << pObj->Name << "   " << pObj->Count << "��        " << pObj->Calculate() << "��" << endl;
				sum += pObj->Calculate();
			}
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << " - �� ���� �ݾ�: " << sum << "��." << endl << endl;
			sum = 0;
		}
	}
	cout << "-------------------------------------------------------------------" << endl;
	cout << "����� �Ϸ��Ͽ����ϴ�." << endl << endl;
	return;
}

void OrderCategory::EditOrder(void)
{
	using namespace std;

	unsigned int index = 0;

	Order* pEditing = 0;
	Object* pEditObj = 0;

	string objName;
	unsigned int objCount;
	string behavior;

	cout << endl << "�ֹ��� �����մϴ�." << endl << endl;

	if (mode == 0) { // ������ ���: ���� �ʿ� ������ ���� �ֱ� �ֹ� �ҷ�����
		if (is_paid == 1) {
			cout << "�ֹ��� �����ϴ�." << endl << endl;
			return;
		}
		pEditing = pOrderList->GetOrder((pOrderList->Count)-1);
	} else { // ������ ���: ���� �Ϸ� ������ ��� �ֹ� ����Ʈ �ҷ�����
		if (pOrderList->Count == 0) {
			cout << "�ֹ��� �����ϴ�." << endl << endl;
			return;
		}
		cout << "> ������ �ֹ� ��ȣ�� �Է��Ͻʽÿ�: ";
		cin >> index;

		if (index >= pOrderList->Count) {
			cout << "�߸��� �ֹ���ȣ �Դϴ�." << endl << endl;
			return;
		}
		pEditing = pOrderList->GetOrder(index);
	}
	
	cout << "> ���� ������ �Է��Ͻʽÿ�([�޴�] [����] [�߰�/����]): ";
	cin >> objName >> objCount >> behavior;

	if (behavior == "�߰�") {
		pEditObj = item.GetObject(objName);
		if (pEditObj == 0) {
			cout << "�޴��� ã�� �� �����ϴ�." << endl << endl;
			return;
		}
		else {
			pEditObj = new Object(objName, pEditObj->Price, objCount);
			pEditing->AddObject(*pEditObj);
			delete pEditObj;
		}
	}
	else if (behavior == "����") {
		pEditObj = pEditing->GetObject(objName);
		if (pEditObj == 0) {
			cout << "�޴��� ã�� �� �����ϴ�." << endl << endl;
			return;
		}
		else {
			pEditObj = new Object(objName, pEditObj->Price, objCount);
			if (pEditing->DeleteObject(*pEditObj)) {
				if (mode == 0) { // ������ ��� (���� �ֱ� �ֹ�)
					pOrderList->DeleteOrder((pOrderList->Count) - 1);
				}
				else {
					pOrderList->DeleteOrder(index);
				}
				is_paid = 1; // �ش� �ֹ��� ��������Ƿ� �ֹ� �Ϸ� ���·� ��ȯ
			}
			delete pEditObj;
		}

	}
	else {
		cout << "�ൿ�� �߸� �Է��Ͽ����ϴ�." << endl << endl;
		return;
	}
	cout << "������ �Ϸ�Ǿ����ϴ�." << endl << endl;
	return;
}

void OrderCategory::AddPayment(void) {
	using namespace std;

	unsigned int calculate = 0;
	Order* pOrder = 0;

	string paymentName;
	Payment* pPayment = 0;
	Pay* pPay = 0;
	PayList* pPayItem = 0;
	string paySuccess;

	// system("cls");

	cout << endl << "<�����ϱ�>" << endl << endl;

	if (is_paid == 0) {
		pOrder = pOrderList->GetOrder((pOrderList->Count) - 1); // ���� �ֱ� �ֹ� �ҷ�����
		calculate = pOrder->Calculate();

		cout << "���� �ݾ�: " << calculate << "��" << endl << endl;

		cout << "���������� �������ּ���. (ī��, ���̹�����, īī������)" << endl;

		pPay = pPayList->AddPay();

		cout << "(0�� �Է��ϸ� �������� ������ �����մϴ�.)" << endl << endl;
		cout << "> ���������� �Է��ϼ���: ";
		cin >> paymentName;

		if (paymentName == "0") {
			cout << "���������� ���õ��� �ʾҽ��ϴ�." << endl;
			return;
		}

		pPayment = payItem.GetPayment(paymentName);
		if (pPayment == 0) {
			cout << "�ش� ���������� �����ϴ�." << endl;
			return;
		}

		cout << endl << paymentName << " ���������� ���õǾ����ϴ�." << endl;
		cout << endl << "> �����Ͻðڽ��ϱ�? ��/�ƴϿ�: ";

		cin >> paySuccess;
		if (paySuccess == "��") {
			pPayment = new Payment(paymentName);
			pPay->AddPayment(*pPayment);
			delete pPayment;

			is_paid = 1; // ���� �Ϸ� ���·� ��ȯ
			pRevManager->Calculate(calculate); // ������ �ݾ� ����� �����ڿ��� �ѱ��
			cout << "���� ����" << endl;
		}
		else {
			cout << "���� ����" << endl;
			cout << "���������� ���õ��� �ʾҽ��ϴ�." << endl << endl;
			return;
		}
		cout << endl << calculate << "���� �����Ǿ����ϴ�." << endl;
		return;
	}
	else { // is_paid == 1�� �� (�ֹ��� 0���� ���� ����)
		cout << "������ �ֹ��� �����ϴ�." << endl;
		return;
	}
}