#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "kiosk_handler.h"
#include <ctime>

OrderCategory::OrderCategory(const MenuItem& item, OrderList* pOrderList, const PayPreset& payItem, PayList* pPayList, RevenueManager* pRevManager) : bPrint(true), item(item), pOrderList(pOrderList), payItem(payItem), pPayList(pPayList), pRevManager(pRevManager)
{
	// ��� ���� �ʱ�ȭ
	mode = 0; // default: ������ ���
	is_paid = 1; // default: ���� �Ϸ�
	is_printed = 1; // default: ��� �Ϸ�
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
	cout << "5. ������ ���" << endl;
	cout << "6. Ű����ũ ����" << endl;
	cout << "---------------------------" << endl << endl;

	cout << "> ������ ��ȣ�� �Է��ϼ���: ";
	cin >> menu;
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
		AddPay();
		break;
	case 5:
		PrintReceipt();
		break;
	case 6:
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
	cout << "2. ����" << endl;
	cout << "3. Ű����ũ ����" << endl;
	cout << "---------------------------" << endl << endl;


	cout << "> (������ ���) ������ ��ȣ�� �Է��ϼ���: ";
	cin >> menu;
	switch (menu) {
	case 1:
		PrintOrder();
		break;
	case 2:
		cout << endl
			<< "���� �� ������� " << pRevManager->Today << "���Դϴ�." << endl << endl;
		break;
	case 3:
		cout << endl << "Ű����ũ�� �����մϴ�." << endl << endl;
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

	cout << "-------------------------------------------------------------------" << endl <<
		"<�޴���>" << endl << endl
		<< "[��ǰ]" << endl
		<< "1. ��� ����: �Ϲݶ��, ���κζ��, �����, ���ζ��, ġ����" << endl
		<< "2. �ʱ� ����: ���ʰ�, �⺻�ʱ�, ���ʰ�" << endl
		<< "3. ���� ����: �����ϰ�, �⺻����, ������" << endl << endl

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
		else {
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


			// ��� �ֹ��� ��쿡�� �ʱ�, ���� ���� ���� 
			if (objName == "�Ϲݶ��" || objName == "���κζ��" || objName == "�����" || objName == "���ζ��" || objName == "ġ����") {
				int ramenPrice = pObj->Price;
			ONE:
				cout << "> �ʱ������� �Է��ϼ���: ";
				cin >> objSpicy;

				if (objSpicy == "0") {
					break;
				}

				pObj = item.GetObject(objSpicy);
				if (pObj == 0) {
					cout << "�ش� �ʱ������� �����ϴ�." << endl;
					goto ONE;
				}


			TWO:
				cout << "> ���������� �Է��ϼ���: ";
				cin >> objCooked;

				if (objCooked == "0") {
					break;
				}

				pObj = item.GetObject(objCooked);
				if (pObj == 0) {
					cout << "�ش� ���������� �����ϴ�." << endl;
					goto TWO;
				}

				cout << "> �ش� �޴��� � �ֹ��Ͻðڽ��ϱ�?: ";
				cin >> objCount;

				if (objCount == 0) {
					break;
				}

				
				pObj = new Object(objName, ramenPrice, objCount);


				pOrder->AddObject(*pObj);

			}
			else {
				cout << "> �ش� �޴��� � �ֹ��Ͻðڽ��ϱ�?: ";
				cin >> objCount;

				if (objCount == 0) {
					break;
				}

				pObj = new Object(objName, pObj->Price, objCount);

				pOrder->AddObject(*pObj);
			}

			if (objName == "�Ϲݶ��" || objName == "���κζ��" || objName == "�����" || objName == "���ζ��" || objName == "ġ����") {
				pObj = new Object(objSpicy, 0, 0);
				pOrder->AddObject(*pObj);

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
	Order* pEditingSpicy1 = 0;
	Object* pEditObjSpicy1 = 0;
	Order* pEditingSpicy2 = 0;
	Object* pEditObjSpicy2 = 0;
	Order* pEditingSpicy3 = 0;
	Object* pEditObjSpicy3 = 0;

	string objSpicy1;
	string objSpicy2;
	string objSpicy3;

	Order* pEditingCooked1 = 0;
	Object* pEditObjCooked1 = 0;
	Order* pEditingCooked2 = 0;
	Object* pEditObjCooked2 = 0;
	Order* pEditingCooked3 = 0;
	Object* pEditObjCooked3 = 0;

	string objCooked1;
	string objCooked2;
	string objCooked3;

	unsigned int objCount;
	string behavior;

	cout << endl << "�ֹ��� �����մϴ�." << endl << endl;

	if (is_paid == 1) {
		cout << "�ֹ��� �����ϴ�." << endl << endl;
		return;
	}
	pEditing = pOrderList->GetOrder((pOrderList->Count) - 1);

	/* } else { // ������ ���: ���� �Ϸ� ������ ��� �ֹ� ����Ʈ �ҷ�����
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
	}*/

	while (true) {
		cout << "> ���� ������ �Է��Ͻʽÿ�([�޴�] [����] [�߰�/����]): ";
		cin >> objName >> objCount >> behavior;

		if (objName == "0") {
			break;
		}

		if (behavior == "�߰�") {
			pEditObj = item.GetObject(objName);
			if (pEditObj == 0) {
				cout << "�޴��� ã�� �� �����ϴ�." << endl << endl;
				continue;
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
				continue;
			}
			else {
				if (objName == "���ʰ�" || objName == "�⺻�ʱ�" || objName == "���ʰ�") {
					pEditObj = new Object(objName, pEditObj->Price, objCount);
					if (pEditing->DeleteObject(*pEditObj)) {
						pOrderList->DeleteOrder((pOrderList->Count) - 1);
						//is_paid = 1;
					}
					delete pEditObj;

					pEditObj = new Object("�⺻�ʱ�", 0, 0);
					pEditing->AddObject(*pEditObj);
					delete pEditObj;

				}
				else if (objName == "�����ϰ�" || objName == "�⺻����" || objName == "������") {
					pEditObj = new Object(objName, pEditObj->Price, objCount);
					if (pEditing->DeleteObject(*pEditObj)) {
						pOrderList->DeleteOrder((pOrderList->Count) - 1);
						//is_paid = 1;
					}
					delete pEditObj;

					pEditObj = new Object("�⺻����", 0, 0);
					pEditing->AddObject(*pEditObj);
					delete pEditObj;

				}
				else if (objName == "�Ϲݶ��" || objName == "���κζ��" || objName == "�����" || objName == "���ζ��" || objName == "ġ����") {
					pEditObj = new Object(objName, pEditObj->Price, objCount);
					if (pEditing->DeleteObject(*pEditObj)) {
						pOrderList->DeleteOrder((pOrderList->Count) - 1);
						is_paid = 1;
					}
					delete pEditObj;

					pEditObj = pEditing->GetObject(objName);
					if (pEditObj == 0) {
						// ����� �ƿ� 0���� ���ŵǴ� ��� �ɼ� ����
						objSpicy1 = "���ʰ�";
						pEditingSpicy1 = pOrderList->GetOrder((pOrderList->Count) - 1);
						pEditObjSpicy1 = pEditing->GetObject(objSpicy1);
						if (pEditObjSpicy1 == 0) {
							objSpicy2 = "�⺻�ʱ�";
							pEditingSpicy2 = pOrderList->GetOrder((pOrderList->Count) - 1);
							pEditObjSpicy2 = pEditing->GetObject(objSpicy2);
							if (pEditObjSpicy2 == 0) {
								objSpicy3 = "���ʰ�";
								pEditingSpicy3 = pOrderList->GetOrder((pOrderList->Count) - 1);
								pEditObjSpicy3 = pEditing->GetObject(objSpicy3);
								pEditObjSpicy3 = new Object(objSpicy3, 0, 0);
								if (pEditingSpicy3->DeleteObject(*pEditObjSpicy3)) {
									pOrderList->DeleteOrder((pOrderList->Count) - 1);
									//is_paid = 1;
								}
								delete pEditObjSpicy3;
							}
							pEditObjSpicy2 = new Object(objSpicy2, 0, 0);
							if (pEditingSpicy2->DeleteObject(*pEditObjSpicy2)) {
								pOrderList->DeleteOrder((pOrderList->Count) - 1);
								//is_paid = 1;
							}
							delete pEditObjSpicy2;
						}
						else {
							pEditObjSpicy1 = new Object(objSpicy1, 0, 0);
							if (pEditingSpicy1->DeleteObject(*pEditObjSpicy1)) {
								pOrderList->DeleteOrder((pOrderList->Count) - 1);
								is_paid = 1;
							}
						}
						delete pEditObjSpicy1;

						objCooked1 = "�����ϰ�";
						pEditingCooked1 = pOrderList->GetOrder((pOrderList->Count) - 1);
						pEditObjCooked1 = pEditing->GetObject(objCooked1);
						if (pEditObjCooked1 == 0) {
							objCooked2 = "�⺻����";
							pEditingCooked2 = pOrderList->GetOrder((pOrderList->Count) - 1);
							pEditObjCooked2 = pEditing->GetObject(objCooked2);
							if (pEditObjCooked2 == 0) {
								objCooked3 = "������";
								pEditingCooked3 = pOrderList->GetOrder((pOrderList->Count) - 1);
								pEditObjCooked3 = pEditing->GetObject(objCooked3);
								pEditObjCooked3 = new Object(objCooked3, 0, 0);
								if (pEditingCooked3->DeleteObject(*pEditObjCooked3)) {
									pOrderList->DeleteOrder((pOrderList->Count) - 1);
									//is_paid = 1;
								}
								delete pEditObjCooked3;
							}
							pEditObjCooked2 = new Object(objCooked2, 0, 0);
							if (pEditingCooked2->DeleteObject(*pEditObjCooked2)) {
								pOrderList->DeleteOrder((pOrderList->Count) - 1);
								//is_paid = 1;
							}
							delete pEditObjCooked2;
						}
						else {
							pEditObjCooked1 = new Object(objCooked1, 0, 0);
							if (pEditingCooked1->DeleteObject(*pEditObjCooked1)) {
								pOrderList->DeleteOrder((pOrderList->Count) - 1);
								//is_paid = 1;
							}
						}
						delete pEditObjCooked1;

					}

				}
				else {
					pEditObj = new Object(objName, pEditObj->Price, objCount);
					if (pEditing->DeleteObject(*pEditObj)) {
						pOrderList->DeleteOrder((pOrderList->Count) - 1);
						is_paid = 1; // �ش� �ֹ��� ��������Ƿ� �ֹ� �Ϸ� ���·� ��ȯ
					}
					delete pEditObj;
				}
			}
		}
		else {
			cout << "�ൿ�� �߸� �Է��Ͽ����ϴ�." << endl << endl;
			return;
		}
		cout << "������ �Ϸ�Ǿ����ϴ�." << endl << endl;
		//return;

		
	}
}

void OrderCategory::AddPay(void) {
	using namespace std;

	unsigned int calculate = 0;
	Order* pOrder = 0;

	string paymentName;
	Payment* pPayItem = 0;
	Pay* pPay = 0;
	string paySuccess;

	cout << endl << "<�����ϱ�>" << endl << endl;

	if (is_paid == 0) {
		pOrder = pOrderList->GetOrder((pOrderList->Count) - 1); // ���� �ֱ� �ֹ� �ҷ�����
		calculate = pOrder->Calculate();

		cout << "���� �ݾ�: " << calculate << "��" << endl << endl;

		cout << "���������� �������ּ���. (ī��, ���̹�����, īī������)" << endl;

		cout << "(0�� �Է��ϸ� �������� ������ �����մϴ�.)" << endl << endl;
		cout << "> ���������� �Է��ϼ���: ";
		cin >> paymentName;

		if (paymentName == "0") {
			cout << "���������� ���õ��� �ʾҽ��ϴ�." << endl;
			return;
		}

		pPayItem = payItem.GetPayment(paymentName);
		if (pPayItem == 0) {
			cout << "�ش� ���������� �����ϴ�." << endl;
			return;
		}

		cout << endl << paymentName << " ���������� ���õǾ����ϴ�." << endl;
		cout << endl << "> �����Ͻðڽ��ϱ�? ��/�ƴϿ�: ";

		cin >> paySuccess;
		if (paySuccess == "��") {
			pPay = pPayList->AddPay();
			pPayItem = new Payment(paymentName);
			pPay->AddPayment(*pPayItem);
			delete pPayItem;

			is_paid = 1; // ���� �Ϸ� ���·� ��ȯ
			pRevManager->Calculate(calculate); // ������ �ݾ� ����� �����ڿ��� �ѱ��
			is_printed = 0; // ����� ������ �������Ƿ� ���� �ʿ� ���·� ��ȯ
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

void OrderCategory::PrintReceipt(void)
{
	using namespace std;

	Order* pOrder = 0;
	Object* pObj = 0;

	Payment* pPayItem = 0;
	Pay* pPay = 0;

	unsigned int sum = 0;
	unsigned int calculate = 0;

	time_t temp;
	struct tm* timeinfo;

	time(&temp);
	timeinfo = localtime(&temp);

	if (is_printed == 0) {
		pOrder = pOrderList->GetOrder((pOrderList->Count) - 1);
		calculate = pOrder->Calculate();

		cout << "<������>" << endl;
		cout << "==============================================" << endl;
		cout << "�����̳� ��鰡��" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "��¥ : " << 1900 + timeinfo->tm_year << "-" << 1 + timeinfo->tm_mon << "-" << timeinfo->tm_mday << " " << timeinfo->tm_hour << ":" << timeinfo->tm_min << endl;
		cout << "----------------------------------------------" << endl;
		cout << "�ֹ���ȣ : " << pOrderList->Count-1 << "�� " << endl;
		cout << "----------------------------------------------" << endl;
		cout << "�޴�\t\t����\t�ݾ�" << endl << endl;
		cout << "----------------------------------------------" << endl;

		for (unsigned int i = 0; i < (pOrder->Count); i++) {
			pObj = pOrder->GetObject(i);
			cout << " ->     " << pObj->Name << "\t\t" << pObj->Count << "\t" << pObj->Calculate() << endl;
			sum += pObj->Calculate();
		}

		pPay = pPayList->GetPay((pPayList->Count) - 1);
		pPayItem = pPay->GetPayment(0); // �׻� 0��° �ڸ��� �����Ƿ�

		cout << "----------------------------------------------" << endl;
		cout << "�հ�\t\t\t\t\t" << sum << "��" << endl << endl;
		cout << "----------------------------------------------" << endl;
		cout << "���� ����\t\t\t" << pPayItem->Name << endl << endl;
		is_printed = 1; // ��� �Ϸ� ���·� ��ȯ
		return;
	}
	else {
		cout << "����� �ֹ��� �����ϴ�." << endl;
		cout << endl << "Ȩ ȭ������ ���ư��ϴ�." << endl << endl;
		return;
	}
}