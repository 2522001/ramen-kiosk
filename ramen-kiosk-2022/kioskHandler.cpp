#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "kioskHandler.h"
#include <ctime>

KioskHandler::KioskHandler(const OrderPreset& orderItem, OrderList* pOrderList, const PayPreset& payItem, PayList* pPayList, RevenueManager* pRevManager) : bPrint(true), orderItem(orderItem), pOrderList(pOrderList), payItem(payItem), pPayList(pPayList), pRevManager(pRevManager)
{
	// ��� ���� �ʱ�ȭ
	mode = 0; // default: ������ ���
	isPaid = 1; // default: ���� �Ϸ�
	isPrinted = 1; // default: ��� �Ϸ�
}

bool KioskHandler::Run(void) {
	using namespace std;

	int menu = 0; // �Է� ��ȣ
	mode = 0;

	cout << "---------------------------" << endl;
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
	case 1:
		NewOrder();
		break;
	case 2:
		CheckOrder();
		break;
	case 3:
		EditOrder();
		break;
	case 4:
		NewPay();
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

bool KioskHandler::Settings(void) {
	using namespace std;

	int menu = 0;
	mode = 1; // ������ ���

	cout << "---------------------------" << endl;
	cout << "�ϴ� ��ȣ�� ������ �� �Է� �� ������ ��带 �����մϴ�." << endl;
	cout << "1. ��ü �ֹ� ���� Ȯ��" << endl;
	cout << "2. ����" << endl;
	cout << "3. Ű����ũ ����" << endl;
	cout << "---------------------------" << endl << endl;


	cout << "> (������ ���) ������ ��ȣ�� �Է��ϼ���: ";
	cin >> menu;
	switch (menu) {
	case 1:
		CheckOrder();
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

void KioskHandler::NewOrder(void) {
	using namespace std;

	string orderItemName;
	string orderItemSpicy;
	string orderItemCooked;

	unsigned int orderItemCount = 0;
	OrderItem* pOrderItem = 0;
	OrderItem* pEditOrderItem = 0;
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

	if (isPaid == 0) {
		cout << "�������� ���� �ֹ��� �ֽ��ϴ�. (���� �ֹ��� ������ 3���� �����Ͽ� �������ּ���.)" << endl
			<< "���� �ֹ��� �����ϰ� ���� �ֹ��Ͻðڽ��ϱ�? ��/�ƴϿ�: ";
		cin >> new_order;
		if (new_order == "��") {
			// ���� �ʿ� ������ ���� �ֹ� ����
			pEditing = pOrderList->GetOrder(pOrderList->Count - 1);

			if (pEditing) {
				// order �� ��� object ����
				for (unsigned int i = 0; i < pEditing->Count; i++) {
					pEditOrderItem = pEditing->GetOrderItem(i);
					pEditOrderItem = new OrderItem(pEditOrderItem->Name, pEditOrderItem->Price, pEditOrderItem->Count);
				}
				if (pEditing->DeleteOrderItem(*pEditOrderItem)) { // object�� ��� ���� �Ǿ� order�� ����ٸ�
					pOrderList->DeleteOrder(pOrderList->Count - 1); // �ش� �ֹ� �ֹ�����Ʈ���� ����

					delete pEditOrderItem;
				}
			}
			cout << "���� �Ϸ�" << endl;

			isPaid = 1;
		}
		else {
			cout << "Ȩ ȭ������ ���ư��ϴ�." << endl;
			return;
		}
	}

	if (isPaid == 1) {
		pOrder = pOrderList->AddOrder();
		while (true) {
			cout << "> �ֹ��� �޴��� �Է��ϼ���: ";
			cin >> orderItemName;

			if (orderItemName == "0") {
				break;
			}

			pOrderItem = orderItem.GetOrderItem(orderItemName);
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

				pOrderItem = orderItem.GetOrderItem(orderItemSpicy);
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

				pOrderItem = orderItem.GetOrderItem(orderItemCooked);
				if (pOrderItem == 0) {
					cout << "�ش� ���������� �����ϴ�." << endl;
					goto TWO;
				}

				cout << "> �ش� �޴��� � �ֹ��Ͻðڽ��ϱ�?: ";
				cin >> orderItemCount;

				if (orderItemCount == 0) {
					break;
				}

				
				pOrderItem = new OrderItem(orderItemName, ramenPrice, orderItemCount);


				pOrder->AddOrderItem(*pOrderItem);

			}
			else {
				cout << "> �ش� �޴��� � �ֹ��Ͻðڽ��ϱ�?: ";
				cin >> orderItemCount;

				if (orderItemCount == 0) {
					break;
				}

				pOrderItem = new OrderItem(orderItemName, pOrderItem->Price, orderItemCount);

				pOrder->AddOrderItem(*pOrderItem);
			}

			if (orderItemName == "�Ϲݶ��" || orderItemName == "���κζ��" || orderItemName == "�����" || orderItemName == "���ζ��" || orderItemName == "ġ����") {
				pOrderItem = new OrderItem(orderItemSpicy, 0, 0);
				pOrder->AddOrderItem(*pOrderItem);

				pOrderItem = new OrderItem(orderItemCooked, 0, 0);

				pOrder->AddOrderItem(*pOrderItem);

			}

			delete pOrderItem;

			cout << endl << "��ٱ��Ͽ� �ֹ��� �߰��Ǿ����ϴ�." << endl << endl;
		}
		if (pOrder->Count == 0) {
			cout << "�ֹ��� �߰����� �ʾҽ��ϴ�." << endl;
			pOrderList->DeleteOrder(pOrderList->Count - 1);

			return;
		}
		isPaid = 0; // ���ο� �ֹ��� �߰��Ǿ����Ƿ� ���� �ʿ� ���·� ��ȯ
		cout << endl << "Ȩ ȭ������ ���ư��ϴ�." << endl << endl;
		return;
	}
}

void KioskHandler::CheckOrder(void) {
	using namespace std;

	Order* pOrder = 0;
	OrderItem* pOrderItem = 0;
	unsigned int sum = 0;
	unsigned int index = 0;

	if (mode == 0) { // ������ ���: ���� �ʿ� ������ ���� �ֱ� �ֹ� ���
		cout << endl << "������ �ֹ��� Ȯ���մϴ�." << endl << endl;
		if (isPaid == 1) {
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
				pOrderItem = pOrder->GetOrderItem(j);
				cout << " ->     " << pOrderItem->Name << "   " << pOrderItem->Count << "��        " << pOrderItem->Calculate() << "��" << endl;
				sum += pOrderItem->Calculate();
			}
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << " - �� ���� �ݾ�: " << sum << "��." << endl << endl;
			sum = 0;
		}
	} else { // ������ ���: ���� �Ϸ� ������ ��� �ֹ� ����Ʈ ���
		if (isPaid == 0) {
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
				pOrderItem = pOrder->GetOrderItem(j);
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

void KioskHandler::EditOrder(void)
{
	using namespace std;

	unsigned int index = 0;

	Order* pEditing = 0;
	OrderItem* pEditOrderItem = 0;

	string orderItemName;
	Order* pEditingSpicy1 = 0;
	OrderItem* pEditOrderItemSpicy1 = 0;
	Order* pEditingSpicy2 = 0;
	OrderItem* pEditOrderItemSpicy2 = 0;
	Order* pEditingSpicy3 = 0;
	OrderItem* pEditOrderItemSpicy3 = 0;

	string orderItemSpicy1;
	string orderItemSpicy2;
	string orderItemSpicy3;

	Order* pEditingCooked1 = 0;
	OrderItem* pEditOrderItemCooked1 = 0;
	Order* pEditingCooked2 = 0;
	OrderItem* pEditOrderItemCooked2 = 0;
	Order* pEditingCooked3 = 0;
	OrderItem* pEditOrderItemCooked3 = 0;

	string orderItemCooked1;
	string orderItemCooked2;
	string orderItemCooked3;

	unsigned int orderItemCount;
	string behavior;

	cout << endl << "�ֹ��� �����մϴ�." << endl << endl;

	if (isPaid == 1) {
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
			pEditOrderItem = orderItem.GetOrderItem(orderItemName);
			if (pEditOrderItem == 0) {
				cout << "�޴��� ã�� �� �����ϴ�." << endl << endl;
				continue;
			}
			else {
				pEditOrderItem = new OrderItem(orderItemName, pEditOrderItem->Price, orderItemCount);
				pEditing->AddOrderItem(*pEditOrderItem);
				delete pEditOrderItem;
			}
		}
		else if (behavior == "����") {
			pEditOrderItem = pEditing->GetOrderItem(orderItemName);
			if (pEditOrderItem == 0) {
				cout << "�޴��� ã�� �� �����ϴ�." << endl << endl;
				continue;
			}
			else {
				if (orderItemName == "���ʰ�" || orderItemName == "�⺻�ʱ�" || orderItemName == "���ʰ�") {
					pEditOrderItem = new OrderItem(orderItemName, pEditOrderItem->Price, orderItemCount);
					if (pEditing->DeleteOrderItem(*pEditOrderItem)) {
						pOrderList->DeleteOrder((pOrderList->Count) - 1);
						isPaid = 1;
					}
					delete pEditOrderItem;

					pEditOrderItem = new OrderItem("�⺻�ʱ�", 0, 0);
					pEditing->AddOrderItem(*pEditOrderItem);
					delete pEditOrderItem;

				}
				else if (orderItemName == "�����ϰ�" || orderItemName == "�⺻����" || orderItemName == "������") {
					pEditOrderItem = new OrderItem(orderItemName, pEditOrderItem->Price, orderItemCount);
					if (pEditing->DeleteOrderItem(*pEditOrderItem)) {
						pOrderList->DeleteOrder((pOrderList->Count) - 1);
					}
					delete pEditOrderItem;

					pEditOrderItem = new OrderItem("�⺻����", 0, 0);
					pEditing->AddOrderItem(*pEditOrderItem);
					delete pEditOrderItem;

				}
				else if (orderItemName == "�Ϲݶ��" || orderItemName == "���κζ��" || orderItemName == "�����" || orderItemName == "���ζ��" || orderItemName == "ġ����") {
					pEditOrderItem = new OrderItem(orderItemName, pEditOrderItem->Price, orderItemCount);
					if (pEditing->DeleteOrderItem(*pEditOrderItem)) {
						pOrderList->DeleteOrder((pOrderList->Count) - 1);
					}
					delete pEditOrderItem;

					pEditOrderItem = pEditing->GetOrderItem(orderItemName);
					if (pEditOrderItem == 0) {
						// ����� �ƿ� 0���� ���ŵǴ� ��� �ɼ� ����
						orderItemSpicy1 = "���ʰ�";
						pEditingSpicy1 = pOrderList->GetOrder((pOrderList->Count) - 1);
						pEditOrderItemSpicy1 = pEditing->GetOrderItem(orderItemSpicy1);
						if (pEditOrderItemSpicy1 == 0) {
							orderItemSpicy2 = "�⺻�ʱ�";
							pEditingSpicy2 = pOrderList->GetOrder((pOrderList->Count) - 1);
							pEditOrderItemSpicy2 = pEditing->GetOrderItem(orderItemSpicy2);
							if (pEditOrderItemSpicy2 == 0) {
								orderItemSpicy3 = "���ʰ�";
								pEditingSpicy3 = pOrderList->GetOrder((pOrderList->Count) - 1);
								pEditOrderItemSpicy3 = pEditing->GetOrderItem(orderItemSpicy3);
								pEditOrderItemSpicy3 = new OrderItem(orderItemSpicy3, 0, 0);
								if (pEditingSpicy3->DeleteOrderItem(*pEditOrderItemSpicy3)) {
									pOrderList->DeleteOrder((pOrderList->Count) - 1);
								}
								delete pEditOrderItemSpicy3;
							}
							pEditOrderItemSpicy2 = new OrderItem(orderItemSpicy2, 0, 0);
							if (pEditingSpicy2->DeleteOrderItem(*pEditOrderItemSpicy2)) {
								pOrderList->DeleteOrder((pOrderList->Count) - 1);
							}
							delete pEditOrderItemSpicy2;
						}
						else {
							pEditOrderItemSpicy1 = new OrderItem(orderItemSpicy1, 0, 0);
							if (pEditingSpicy1->DeleteOrderItem(*pEditOrderItemSpicy1)) {
								pOrderList->DeleteOrder((pOrderList->Count) - 1);
								isPaid = 1;
							}
						}
						delete pEditOrderItemSpicy1;

						orderItemCooked1 = "�����ϰ�";
						pEditingCooked1 = pOrderList->GetOrder((pOrderList->Count) - 1);
						pEditOrderItemCooked1 = pEditing->GetOrderItem(orderItemCooked1);
						if (pEditOrderItemCooked1 == 0) {
							orderItemCooked2 = "�⺻����";
							pEditingCooked2 = pOrderList->GetOrder((pOrderList->Count) - 1);
							pEditOrderItemCooked2 = pEditing->GetOrderItem(orderItemCooked2);
							if (pEditOrderItemCooked2 == 0) {
								orderItemCooked3 = "������";
								pEditingCooked3 = pOrderList->GetOrder((pOrderList->Count) - 1);
								pEditOrderItemCooked3 = pEditing->GetOrderItem(orderItemCooked3);
								pEditOrderItemCooked3 = new OrderItem(orderItemCooked3, 0, 0);
								if (pEditingCooked3->DeleteOrderItem(*pEditOrderItemCooked3)) {
									pOrderList->DeleteOrder((pOrderList->Count) - 1);
								}
								delete pEditOrderItemCooked3;
							}
							pEditOrderItemCooked2 = new OrderItem(orderItemCooked2, 0, 0);
							if (pEditingCooked2->DeleteOrderItem(*pEditOrderItemCooked2)) {
								pOrderList->DeleteOrder((pOrderList->Count) - 1);
							}
							delete pEditOrderItemCooked2;
						}
						else {
							pEditOrderItemCooked1 = new OrderItem(orderItemCooked1, 0, 0);
							if (pEditingCooked1->DeleteOrderItem(*pEditOrderItemCooked1)) {
								pOrderList->DeleteOrder((pOrderList->Count) - 1);
							}
						}
						delete pEditOrderItemCooked1;

					}

				}
				else {
					pEditOrderItem = new OrderItem(orderItemName, pEditOrderItem->Price, orderItemCount);
					if (pEditing->DeleteOrderItem(*pEditOrderItem)) {
						pOrderList->DeleteOrder((pOrderList->Count) - 1);
						isPaid = 1; // �ش� �ֹ��� ��������Ƿ� �ֹ� �Ϸ� ���·� ��ȯ
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

void KioskHandler::NewPay(void) {
	using namespace std;

	unsigned int calculate = 0;
	Order* pOrder = 0;

	string payItemName;
	PayItem* pPayItem = 0;
	Pay* pPay = 0;
	string paySuccess;

	cout << endl << "<�����ϱ�>" << endl << endl;

	if (isPaid == 0) {
		pOrder = pOrderList->GetOrder((pOrderList->Count) - 1); // ���� �ֱ� �ֹ� �ҷ�����
		calculate = pOrder->Calculate();

		cout << "���� �ݾ�: " << calculate << "��" << endl << endl;

		cout << "���������� �������ּ���. (ī��, ���̹�����, īī������)" << endl;

		cout << "(0�� �Է��ϸ� �������� ������ �����մϴ�.)" << endl << endl;
		cout << "> ���������� �Է��ϼ���: ";
		cin >> payItemName;

		if (payItemName == "0") {
			cout << "���������� ���õ��� �ʾҽ��ϴ�." << endl;
			return;
		}

		pPayItem = payItem.GetPayItem(payItemName);
		if (pPayItem == 0) {
			cout << "�ش� ���������� �����ϴ�." << endl;
			return;
		}

		cout << endl << payItemName << " ���������� ���õǾ����ϴ�." << endl;
		cout << endl << "> �����Ͻðڽ��ϱ�? ��/�ƴϿ�: ";

		cin >> paySuccess;
		if (paySuccess == "��") {
			pPay = pPayList->AddPay();
			pPayItem = new PayItem(payItemName);
			pPay->AddPayItem(*pPayItem);
			delete pPayItem;

			isPaid = 1; // ���� �Ϸ� ���·� ��ȯ
			pRevManager->Calculate(calculate); // ������ �ݾ� ����� �����ڿ��� �ѱ��
			isPrinted = 0; // ����� ������ �������Ƿ� ���� �ʿ� ���·� ��ȯ
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
	else { // isPaid == 1�� �� (�ֹ��� 0���� ���� ����)
		cout << "������ �ֹ��� �����ϴ�." << endl;
		return;
	}
}

void KioskHandler::PrintReceipt(void)
{
	using namespace std;

	Order* pOrder = 0;
	OrderItem* pOrderItem = 0;

	PayItem* pPayItem = 0;
	Pay* pPay = 0;

	unsigned int sum = 0;
	unsigned int calculate = 0;

	time_t temp;
	struct tm* timeinfo;

	time(&temp);
	timeinfo = localtime(&temp);

	if (isPrinted == 0) {
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
			pOrderItem = pOrder->GetOrderItem(i);
			cout << " ->     " << pOrderItem->Name << "\t\t" << pOrderItem->Count << "\t" << pOrderItem->Calculate() << endl;
			sum += pOrderItem->Calculate();
		}

		pPay = pPayList->GetPay((pPayList->Count) - 1);
		pPayItem = pPay->GetPayItem(0); // �׻� 0��° �ڸ��� �����Ƿ�

		cout << "----------------------------------------------" << endl;
		cout << "�հ�\t\t\t\t\t" << sum << "��" << endl << endl;
		cout << "----------------------------------------------" << endl;
		cout << "���� ����\t\t\t" << pPayItem->Name << endl << endl;
		isPrinted = 1; // ��� �Ϸ� ���·� ��ȯ
		return;
	}
	else {
		cout << "����� �ֹ��� �����ϴ�." << endl;
		cout << endl << "Ȩ ȭ������ ���ư��ϴ�." << endl << endl;
		return;
	}
}