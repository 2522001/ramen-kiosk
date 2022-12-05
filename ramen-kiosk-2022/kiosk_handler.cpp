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

	string orderItemName;
	string orderItemSpicy;
	string orderItemCooked;

	unsigned int orderItemCount = 0;
	Object* pOrderItem = 0;
	Object* pEditOrderItem = 0;
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
					pEditOrderItem = pEditing->GetObject(i);
					pEditOrderItem = new Object(pEditOrderItem->Name, pEditOrderItem->Price, pEditOrderItem->Count);
				}
				if (pEditing->DeleteObject(*pEditOrderItem)) { // object�� ��� ���� �Ǿ� order�� ����ٸ�
					pOrderList->DeleteOrder(pOrderList->Count - 1); // �ش� �ֹ� �ֹ�����Ʈ���� ����

					delete pEditOrderItem;
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
			cin >> orderItemName;

			if (orderItemName == "0") {
				break;
			}

			pOrderItem = item.GetObject(orderItemName);
			if (pOrderItem == 0) {
				cout << "�ش� �޴��� �����ϴ�." << endl;
				continue;
			}


			// ��� �ֹ��� ��쿡�� �ʱ�, ���� ���� ���� 
			if (orderItemName == "�Ϲݶ��" || orderItemName == "���κζ��" || orderItemName == "�����" || orderItemName == "���ζ��" || orderItemName == "ġ����") {
				int ramenPrice = pOrderItem->Price;
			ONE:
				cout << "> �ʱ������� �Է��ϼ���: ";
				cin >> orderItemSpicy;

				if (orderItemSpicy == "0") {
					break;
				}

				pOrderItem = item.GetObject(orderItemSpicy);
				if (pOrderItem == 0) {
					cout << "�ش� �ʱ������� �����ϴ�." << endl;
					goto ONE;
				}


			TWO:
				cout << "> ���������� �Է��ϼ���: ";
				cin >> orderItemCooked;

				if (orderItemCooked == "0") {
					break;
				}

				pOrderItem = item.GetObject(orderItemCooked);
				if (pOrderItem == 0) {
					cout << "�ش� ���������� �����ϴ�." << endl;
					goto TWO;
				}

				cout << "> �ش� �޴��� � �ֹ��Ͻðڽ��ϱ�?: ";
				cin >> orderItemCount;

				if (orderItemCount == 0) {
					break;
				}

				
				pOrderItem = new Object(orderItemName, ramenPrice, orderItemCount);


				pOrder->AddObject(*pOrderItem);

			}
			else {
				cout << "> �ش� �޴��� � �ֹ��Ͻðڽ��ϱ�?: ";
				cin >> orderItemCount;

				if (orderItemCount == 0) {
					break;
				}

				pOrderItem = new Object(orderItemName, pOrderItem->Price, orderItemCount);

				pOrder->AddObject(*pOrderItem);
			}

			if (orderItemName == "�Ϲݶ��" || orderItemName == "���κζ��" || orderItemName == "�����" || orderItemName == "���ζ��" || orderItemName == "ġ����") {
				pOrderItem = new Object(orderItemSpicy, 0, 0);
				pOrder->AddObject(*pOrderItem);

				pOrderItem = new Object(orderItemCooked, 0, 0);

				pOrder->AddObject(*pOrderItem);

			}

			delete pOrderItem;

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
	Object* pOrderItem = 0;
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
				pOrderItem = pOrder->GetObject(j);
				cout << " ->     " << pOrderItem->Name << "   " << pOrderItem->Count << "��        " << pOrderItem->Calculate() << "��" << endl;
				sum += pOrderItem->Calculate();
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
				pOrderItem = pOrder->GetObject(j);
				cout << " ->     " << pOrderItem->Name << "   " << pOrderItem->Count << "��        " << pOrderItem->Calculate() << "��" << endl;
				sum += pOrderItem->Calculate();
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
	Object* pEditOrderItem = 0;

	string orderItemName;
	Order* pEditingSpicy1 = 0;
	Object* pEditOrderItemSpicy1 = 0;
	Order* pEditingSpicy2 = 0;
	Object* pEditOrderItemSpicy2 = 0;
	Order* pEditingSpicy3 = 0;
	Object* pEditOrderItemSpicy3 = 0;

	string orderItemSpicy1;
	string orderItemSpicy2;
	string orderItemSpicy3;

	Order* pEditingCooked1 = 0;
	Object* pEditOrderItemCooked1 = 0;
	Order* pEditingCooked2 = 0;
	Object* pEditOrderItemCooked2 = 0;
	Order* pEditingCooked3 = 0;
	Object* pEditOrderItemCooked3 = 0;

	string orderItemCooked1;
	string orderItemCooked2;
	string orderItemCooked3;

	unsigned int orderItemCount;
	string behavior;

	cout << endl << "�ֹ��� �����մϴ�." << endl << endl;

	if (is_paid == 1) {
		cout << "�ֹ��� �����ϴ�." << endl << endl;
		return;
	}
	pEditing = pOrderList->GetOrder((pOrderList->Count) - 1);

	while (true) {
		cout << "> ���� ������ �Է��Ͻʽÿ�([�޴�] [����] [�߰�/����]): ";
		cin >> orderItemName >> orderItemCount >> behavior;

		if (orderItemName == "0") {
			break;
		}

		if (behavior == "�߰�") {
			pEditOrderItem = item.GetObject(orderItemName);
			if (pEditOrderItem == 0) {
				cout << "�޴��� ã�� �� �����ϴ�." << endl << endl;
				continue;
			}
			else {
				pEditOrderItem = new Object(orderItemName, pEditOrderItem->Price, orderItemCount);
				pEditing->AddObject(*pEditOrderItem);
				delete pEditOrderItem;
			}
		}
		else if (behavior == "����") {
			pEditOrderItem = pEditing->GetObject(orderItemName);
			if (pEditOrderItem == 0) {
				cout << "�޴��� ã�� �� �����ϴ�." << endl << endl;
				continue;
			}
			else {
				if (orderItemName == "���ʰ�" || orderItemName == "�⺻�ʱ�" || orderItemName == "���ʰ�") {
					pEditOrderItem = new Object(orderItemName, pEditOrderItem->Price, orderItemCount);
					if (pEditing->DeleteObject(*pEditOrderItem)) {
						pOrderList->DeleteOrder((pOrderList->Count) - 1);
						//is_paid = 1;
					}
					delete pEditOrderItem;

					pEditOrderItem = new Object("�⺻�ʱ�", 0, 0);
					pEditing->AddObject(*pEditOrderItem);
					delete pEditOrderItem;

				}
				else if (orderItemName == "�����ϰ�" || orderItemName == "�⺻����" || orderItemName == "������") {
					pEditOrderItem = new Object(orderItemName, pEditOrderItem->Price, orderItemCount);
					if (pEditing->DeleteObject(*pEditOrderItem)) {
						pOrderList->DeleteOrder((pOrderList->Count) - 1);
						//is_paid = 1;
					}
					delete pEditOrderItem;

					pEditOrderItem = new Object("�⺻����", 0, 0);
					pEditing->AddObject(*pEditOrderItem);
					delete pEditOrderItem;

				}
				else if (orderItemName == "�Ϲݶ��" || orderItemName == "���κζ��" || orderItemName == "�����" || orderItemName == "���ζ��" || orderItemName == "ġ����") {
					pEditOrderItem = new Object(orderItemName, pEditOrderItem->Price, orderItemCount);
					if (pEditing->DeleteObject(*pEditOrderItem)) {
						pOrderList->DeleteOrder((pOrderList->Count) - 1);
						is_paid = 1;
					}
					delete pEditOrderItem;

					pEditOrderItem = pEditing->GetObject(orderItemName);
					if (pEditOrderItem == 0) {
						// ����� �ƿ� 0���� ���ŵǴ� ��� �ɼ� ����
						orderItemSpicy1 = "���ʰ�";
						pEditingSpicy1 = pOrderList->GetOrder((pOrderList->Count) - 1);
						pEditOrderItemSpicy1 = pEditing->GetObject(orderItemSpicy1);
						if (pEditOrderItemSpicy1 == 0) {
							orderItemSpicy2 = "�⺻�ʱ�";
							pEditingSpicy2 = pOrderList->GetOrder((pOrderList->Count) - 1);
							pEditOrderItemSpicy2 = pEditing->GetObject(orderItemSpicy2);
							if (pEditOrderItemSpicy2 == 0) {
								orderItemSpicy3 = "���ʰ�";
								pEditingSpicy3 = pOrderList->GetOrder((pOrderList->Count) - 1);
								pEditOrderItemSpicy3 = pEditing->GetObject(orderItemSpicy3);
								pEditOrderItemSpicy3 = new Object(orderItemSpicy3, 0, 0);
								if (pEditingSpicy3->DeleteObject(*pEditOrderItemSpicy3)) {
									pOrderList->DeleteOrder((pOrderList->Count) - 1);
									//is_paid = 1;
								}
								delete pEditOrderItemSpicy3;
							}
							pEditOrderItemSpicy2 = new Object(orderItemSpicy2, 0, 0);
							if (pEditingSpicy2->DeleteObject(*pEditOrderItemSpicy2)) {
								pOrderList->DeleteOrder((pOrderList->Count) - 1);
								//is_paid = 1;
							}
							delete pEditOrderItemSpicy2;
						}
						else {
							pEditOrderItemSpicy1 = new Object(orderItemSpicy1, 0, 0);
							if (pEditingSpicy1->DeleteObject(*pEditOrderItemSpicy1)) {
								pOrderList->DeleteOrder((pOrderList->Count) - 1);
								is_paid = 1;
							}
						}
						delete pEditOrderItemSpicy1;

						orderItemCooked1 = "�����ϰ�";
						pEditingCooked1 = pOrderList->GetOrder((pOrderList->Count) - 1);
						pEditOrderItemCooked1 = pEditing->GetObject(orderItemCooked1);
						if (pEditOrderItemCooked1 == 0) {
							orderItemCooked2 = "�⺻����";
							pEditingCooked2 = pOrderList->GetOrder((pOrderList->Count) - 1);
							pEditOrderItemCooked2 = pEditing->GetObject(orderItemCooked2);
							if (pEditOrderItemCooked2 == 0) {
								orderItemCooked3 = "������";
								pEditingCooked3 = pOrderList->GetOrder((pOrderList->Count) - 1);
								pEditOrderItemCooked3 = pEditing->GetObject(orderItemCooked3);
								pEditOrderItemCooked3 = new Object(orderItemCooked3, 0, 0);
								if (pEditingCooked3->DeleteObject(*pEditOrderItemCooked3)) {
									pOrderList->DeleteOrder((pOrderList->Count) - 1);
									//is_paid = 1;
								}
								delete pEditOrderItemCooked3;
							}
							pEditOrderItemCooked2 = new Object(orderItemCooked2, 0, 0)orderItemCooked;
							if (pEditingCooked2->DeleteObject(*pEditOrderItemCooked2)) {
								pOrderList->DeleteOrder((pOrderList->Count) - 1);
								//is_paid = 1;
							}
							delete pEditOrderItemCooked2;
						}
						else {
							pEditOrderItemCooked1 = new Object(orderItemCooked1, 0, 0);
							if (pEditingCooked1->DeleteObject(*pEditOrderItemCooked1)) {
								pOrderList->DeleteOrder((pOrderList->Count) - 1);
								//is_paid = 1;
							}
						}
						delete pEditOrderItemCooked1;

					}

				}
				else {
					pEditOrderItem = new Object(orderItemName, pEditOrderItem->Price, orderItemCount);
					if (pEditing->DeleteObject(*pEditOrderItem)) {
						pOrderList->DeleteOrder((pOrderList->Count) - 1);
						is_paid = 1; // �ش� �ֹ��� ��������Ƿ� �ֹ� �Ϸ� ���·� ��ȯ
					}
					delete pEditOrderItem;
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
	Object* pOrderItem = 0;

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
			pOrderItem = pOrder->GetObject(i);
			cout << " ->     " << pOrderItem->Name << "\t\t" << pOrderItem->Count << "\t" << pOrderItem->Calculate() << endl;
			sum += pOrderItem->Calculate();
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