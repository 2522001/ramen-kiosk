#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "kiosk_handler.h"
#include <ctime>

OrderCategory::OrderCategory(const MenuItem& item, OrderList* pOrderList, const PayPreset& payItem, PayList* pPayList, RevenueManager* pRevManager) : bPrint(true), item(item), pOrderList(pOrderList), payItem(payItem), pPayList(pPayList), pRevManager(pRevManager)
{
	// 멤버 변수 초기화
	mode = 0; // default: 구매자 모드
	is_paid = 1; // default: 결제 완료
	is_printed = 1; // default: 출력 완료
}

bool OrderCategory::Run(void) {
	using namespace std;

	int menu = 0; // 입력 번호 (변수명 맞춰야할듯)
	mode = 0;

	cout << "---------------------------" << endl;
	cout << "<성훈이네 라면가게>" << endl;
	cout << "1. 새로운 주문" << endl;
	cout << "2. 주문 확인" << endl;
	cout << "3. 주문 수정" << endl;
	cout << "4. 결제" << endl;
	cout << "5. 영수증 출력" << endl;
	cout << "6. 키오스크 설정" << endl;
	cout << "---------------------------" << endl << endl;

	cout << "> 선택지 번호를 입력하세요: ";
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
		cout << "잘못 입력하셨습니다." << endl << "메뉴를 다시 출력합니다." << endl;
		bPrint = true;
		break;

	}
	return true;
}

bool OrderCategory::Settings(void) {
	using namespace std;

	int menu = 0; // 입력 번호 (변수명 맞춰야할듯)
	mode = 1; // 관리자 모드

	cout << "---------------------------" << endl;
	cout << "<관리자 모드>" << endl;
	cout << "하단 번호를 제외한 값 입력 시 관리자 모드를 종료합니다." << endl;
	cout << "1. 전체 주문 내역 확인" << endl;
	cout << "2. 정산" << endl;
	cout << "3. 키오스크 종료" << endl;
	cout << "---------------------------" << endl << endl;


	cout << "> (관리자 모드) 선택지 번호를 입력하세요: ";
	cin >> menu;
	switch (menu) {
	case 1:
		PrintOrder();
		break;
	case 2:
		cout << endl
			<< "현재 총 매출액은 " << pRevManager->Today << "원입니다." << endl << endl;
		break;
	case 3:
		cout << endl << "키오스크를 종료합니다." << endl << endl;
		exit(0);
	default:
		cout << endl << "홈 화면으로 돌아갑니다." << endl << endl;
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
		"<메뉴판>" << endl << endl
		<< "[단품]" << endl
		<< "1. 라면 종류: 일반라면, 순두부라면, 떡라면, 만두라면, 치즈라면" << endl
		<< "2. 맵기 정도: 덜맵게, 기본맵기, 더맵게" << endl
		<< "3. 익힘 정도: 꼬들하게, 기본익힘, 퍼지게" << endl << endl

		<< "[음료]" << endl
		<< "1. 콜라" << endl
		<< "2. 사이다" << endl << endl

		<< "[반찬]" << endl
		<< "1. 단무지" << endl
		<< "2. 김치" << endl << endl

		<< "[세트메뉴]" << endl
		<< "1. 세트 메뉴 1번: 라면 2개 + 음료 1개 + 반찬 1개" << endl
		<< "2. 세트 메뉴 1번: 라면 1개 + 음료 1개 + 반찬 1개" << endl

		<< "-------------------------------------------------------------------" << endl << endl
		<< "-->입력형식 : 메뉴 이름" << endl;

	cout << "(0을 입력하면 메뉴 주문을 종료합니다.)" << endl << endl;

	if (is_paid == 0) {
		cout << "결제하지 않은 주문이 있습니다. (기존 주문의 수정은 3번을 선택하여 진행해주세요.)" << endl
			<< "이전 주문을 삭제하고 새로 주문하시겠습니까? 네/아니요: ";
		cin >> new_order;
		if (new_order == "네") {
			// 결제 필요 상태의 이전 주문 삭제
			pEditing = pOrderList->GetOrder(pOrderList->Count - 1);

			if (pEditing) {
				// order 내 모든 object 삭제
				for (unsigned int i = 0; i < pEditing->Count; i++) {
					pEditOrderItem = pEditing->GetObject(i);
					pEditOrderItem = new Object(pEditOrderItem->Name, pEditOrderItem->Price, pEditOrderItem->Count);
				}
				if (pEditing->DeleteObject(*pEditOrderItem)) { // object가 모두 삭제 되어 order가 비었다면
					pOrderList->DeleteOrder(pOrderList->Count - 1); // 해당 주문 주문리스트에서 삭제

					delete pEditOrderItem;
				}
			}
			cout << "삭제 완료" << endl;

			is_paid = 1;
		}
		else {
			cout << "홈 화면으로 돌아갑니다." << endl;
			return;
		}
	}

	if (is_paid == 1) {
		pOrder = pOrderList->AddOrder();
		while (true) {
			cout << "> 주문할 메뉴를 입력하세요: ";
			cin >> orderItemName;

			if (orderItemName == "0") {
				break;
			}

			pOrderItem = item.GetObject(orderItemName);
			if (pOrderItem == 0) {
				cout << "해당 메뉴는 없습니다." << endl;
				continue;
			}


			// 라면 주문인 경우에만 맵기, 익힘 정도 선택 
			if (orderItemName == "일반라면" || orderItemName == "순두부라면" || orderItemName == "떡라면" || orderItemName == "만두라면" || orderItemName == "치즈라면") {
				int ramenPrice = pOrderItem->Price;
			ONE:
				cout << "> 맵기정도를 입력하세요: ";
				cin >> orderItemSpicy;

				if (orderItemSpicy == "0") {
					break;
				}

				pOrderItem = item.GetObject(orderItemSpicy);
				if (pOrderItem == 0) {
					cout << "해당 맵기정도는 없습니다." << endl;
					goto ONE;
				}


			TWO:
				cout << "> 익힘정도를 입력하세요: ";
				cin >> orderItemCooked;

				if (orderItemCooked == "0") {
					break;
				}

				pOrderItem = item.GetObject(orderItemCooked);
				if (pOrderItem == 0) {
					cout << "해당 익힘정도는 없습니다." << endl;
					goto TWO;
				}

				cout << "> 해당 메뉴를 몇개 주문하시겠습니까?: ";
				cin >> orderItemCount;

				if (orderItemCount == 0) {
					break;
				}

				
				pOrderItem = new Object(orderItemName, ramenPrice, orderItemCount);


				pOrder->AddObject(*pOrderItem);

			}
			else {
				cout << "> 해당 메뉴를 몇개 주문하시겠습니까?: ";
				cin >> orderItemCount;

				if (orderItemCount == 0) {
					break;
				}

				pOrderItem = new Object(orderItemName, pOrderItem->Price, orderItemCount);

				pOrder->AddObject(*pOrderItem);
			}

			if (orderItemName == "일반라면" || orderItemName == "순두부라면" || orderItemName == "떡라면" || orderItemName == "만두라면" || orderItemName == "치즈라면") {
				pOrderItem = new Object(orderItemSpicy, 0, 0);
				pOrder->AddObject(*pOrderItem);

				pOrderItem = new Object(orderItemCooked, 0, 0);

				pOrder->AddObject(*pOrderItem);

			}

			delete pOrderItem;

			cout << endl << "장바구니에 주문이 추가되었습니다." << endl << endl;
		}
		if (pOrder->Count == 0) {
			cout << "주문이 추가되지 않았습니다." << endl;
			pOrderList->DeleteOrder(pOrderList->Count - 1);

			return;
		}
		is_paid = 0; // 새로운 주문이 추가되었으므로 결제 필요 상태로 전환
		cout << endl << "홈 화면으로 돌아갑니다." << endl << endl;
		return;
	}
}

void OrderCategory::PrintOrder(void) {
	using namespace std;

	Order* pOrder = 0;
	Object* pOrderItem = 0;
	unsigned int sum = 0;
	unsigned int index = 0;

	if (mode == 0) { // 구매자 모드: 결제 필요 상태의 가장 최근 주문 출력
		cout << endl << "결제할 주문을 확인합니다." << endl << endl;
		if (is_paid == 1) {
			cout << "주문이 없습니다." << endl << endl;
			return;
		}
		else {
			pOrder = pOrderList->GetOrder((pOrderList->Count) - 1);
			cout << "<장바구니>" << endl;
			cout << "-------------------------------------------------------------------" << endl << endl;
			cout << "[주문번호 " << (pOrderList->Count) - 1 << "번] " << endl << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << "(주문내역)" << endl << endl;
			for (unsigned int j = 0; j < pOrder->Count; j++) {
				pOrderItem = pOrder->GetObject(j);
				cout << " ->     " << pOrderItem->Name << "   " << pOrderItem->Count << "개        " << pOrderItem->Calculate() << "원" << endl;
				sum += pOrderItem->Calculate();
			}
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << " - 총 결제 금액: " << sum << "원." << endl << endl;
			sum = 0;
		}
	} else { // 관리자 모드: 결제 완료 상태의 모든 주문 리스트 출력
		if (is_paid == 0) {
			index = pOrderList->Count - 1; // 가장 최근 주문이 결제 필요 상태인 경우 해당 주문 빼고 출력
		}
		else {
			index = pOrderList->Count;
		}
		cout << endl << "전체 주문 내역을 확인합니다." << endl << endl;
		if (pOrderList->Count == 0) {
			cout << "주문이 없습니다." << endl << endl;
			return;
		}
		for (unsigned int i = 0; i < index; i++) {
			pOrder = pOrderList->GetOrder(i);

			cout << "<장바구니>" << endl;
			cout << "-------------------------------------------------------------------" << endl << endl;
			cout << "[주문번호 " << i << "번] " << endl << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << "(주문내역)" << endl << endl;
			//cout << "        (메뉴)               (수량)      (금액)   " << endl;
			for (unsigned int j = 0; j < pOrder->Count; j++) {
				pOrderItem = pOrder->GetObject(j);
				cout << " ->     " << pOrderItem->Name << "   " << pOrderItem->Count << "개        " << pOrderItem->Calculate() << "원" << endl;
				sum += pOrderItem->Calculate();
			}
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << " - 총 결제 금액: " << sum << "원." << endl << endl;
			sum = 0;
		}
	}
	cout << "-------------------------------------------------------------------" << endl;
	cout << "출력을 완료하였습니다." << endl << endl;
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

	cout << endl << "주문을 수정합니다." << endl << endl;

	if (is_paid == 1) {
		cout << "주문이 없습니다." << endl << endl;
		return;
	}
	pEditing = pOrderList->GetOrder((pOrderList->Count) - 1);

	while (true) {
		cout << "> 수정 서식을 입력하십시오([메뉴] [개수] [추가/제거]): ";
		cin >> orderItemName >> orderItemCount >> behavior;

		if (orderItemName == "0") {
			break;
		}

		if (behavior == "추가") {
			pEditOrderItem = item.GetObject(orderItemName);
			if (pEditOrderItem == 0) {
				cout << "메뉴를 찾을 수 없습니다." << endl << endl;
				continue;
			}
			else {
				pEditOrderItem = new Object(orderItemName, pEditOrderItem->Price, orderItemCount);
				pEditing->AddObject(*pEditOrderItem);
				delete pEditOrderItem;
			}
		}
		else if (behavior == "제거") {
			pEditOrderItem = pEditing->GetObject(orderItemName);
			if (pEditOrderItem == 0) {
				cout << "메뉴를 찾을 수 없습니다." << endl << endl;
				continue;
			}
			else {
				if (orderItemName == "덜맵게" || orderItemName == "기본맵기" || orderItemName == "더맵게") {
					pEditOrderItem = new Object(orderItemName, pEditOrderItem->Price, orderItemCount);
					if (pEditing->DeleteObject(*pEditOrderItem)) {
						pOrderList->DeleteOrder((pOrderList->Count) - 1);
						//is_paid = 1;
					}
					delete pEditOrderItem;

					pEditOrderItem = new Object("기본맵기", 0, 0);
					pEditing->AddObject(*pEditOrderItem);
					delete pEditOrderItem;

				}
				else if (orderItemName == "꼬들하게" || orderItemName == "기본익힘" || orderItemName == "퍼지게") {
					pEditOrderItem = new Object(orderItemName, pEditOrderItem->Price, orderItemCount);
					if (pEditing->DeleteObject(*pEditOrderItem)) {
						pOrderList->DeleteOrder((pOrderList->Count) - 1);
						//is_paid = 1;
					}
					delete pEditOrderItem;

					pEditOrderItem = new Object("기본익힘", 0, 0);
					pEditing->AddObject(*pEditOrderItem);
					delete pEditOrderItem;

				}
				else if (orderItemName == "일반라면" || orderItemName == "순두부라면" || orderItemName == "떡라면" || orderItemName == "만두라면" || orderItemName == "치즈라면") {
					pEditOrderItem = new Object(orderItemName, pEditOrderItem->Price, orderItemCount);
					if (pEditing->DeleteObject(*pEditOrderItem)) {
						pOrderList->DeleteOrder((pOrderList->Count) - 1);
						is_paid = 1;
					}
					delete pEditOrderItem;

					pEditOrderItem = pEditing->GetObject(orderItemName);
					if (pEditOrderItem == 0) {
						// 라면이 아예 0개로 제거되는 경우 옵션 삭제
						orderItemSpicy1 = "덜맵게";
						pEditingSpicy1 = pOrderList->GetOrder((pOrderList->Count) - 1);
						pEditOrderItemSpicy1 = pEditing->GetObject(orderItemSpicy1);
						if (pEditOrderItemSpicy1 == 0) {
							orderItemSpicy2 = "기본맵기";
							pEditingSpicy2 = pOrderList->GetOrder((pOrderList->Count) - 1);
							pEditOrderItemSpicy2 = pEditing->GetObject(orderItemSpicy2);
							if (pEditOrderItemSpicy2 == 0) {
								orderItemSpicy3 = "더맵게";
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

						orderItemCooked1 = "꼬들하게";
						pEditingCooked1 = pOrderList->GetOrder((pOrderList->Count) - 1);
						pEditOrderItemCooked1 = pEditing->GetObject(orderItemCooked1);
						if (pEditOrderItemCooked1 == 0) {
							orderItemCooked2 = "기본익힘";
							pEditingCooked2 = pOrderList->GetOrder((pOrderList->Count) - 1);
							pEditOrderItemCooked2 = pEditing->GetObject(orderItemCooked2);
							if (pEditOrderItemCooked2 == 0) {
								orderItemCooked3 = "퍼지게";
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
						is_paid = 1; // 해당 주문이 사라졌으므로 주문 완료 상태로 전환
					}
					delete pEditOrderItem;
				}
			}
		}
		else {
			cout << "행동을 잘못 입력하였습니다." << endl << endl;
			return;
		}
		cout << "수정이 완료되었습니다." << endl << endl;
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

	cout << endl << "<결제하기>" << endl << endl;

	if (is_paid == 0) {
		pOrder = pOrderList->GetOrder((pOrderList->Count) - 1); // 가장 최근 주문 불러오기
		calculate = pOrder->Calculate();

		cout << "결제 금액: " << calculate << "원" << endl << endl;

		cout << "결제수단을 선택해주세요. (카드, 네이버페이, 카카오페이)" << endl;

		cout << "(0을 입력하면 결제수단 선택을 종료합니다.)" << endl << endl;
		cout << "> 결제수단을 입력하세요: ";
		cin >> paymentName;

		if (paymentName == "0") {
			cout << "결제수단이 선택되지 않았습니다." << endl;
			return;
		}

		pPayItem = payItem.GetPayment(paymentName);
		if (pPayItem == 0) {
			cout << "해당 결제수단은 없습니다." << endl;
			return;
		}

		cout << endl << paymentName << " 결제수단이 선택되었습니다." << endl;
		cout << endl << "> 결제하시겠습니까? 네/아니요: ";

		cin >> paySuccess;
		if (paySuccess == "네") {
			pPay = pPayList->AddPay();
			pPayItem = new Payment(paymentName);
			pPay->AddPayment(*pPayItem);
			delete pPayItem;

			is_paid = 1; // 결제 완료 상태로 전환
			pRevManager->Calculate(calculate); // 결제된 금액 매출액 관리자에게 넘기기
			is_printed = 0; // 출력할 내역이 생겼으므로 결제 필요 상태로 전환
			cout << "결제 성공" << endl;
		}
		else {
			cout << "결제 오류" << endl;
			cout << "결제수단이 선택되지 않았습니다." << endl << endl;
			return;
		}
		cout << endl << calculate << "원이 결제되었습니다." << endl;
		return;
	}
	else { // is_paid == 1일 때 (주문이 0개인 상태 포함)
		cout << "결제할 주문이 없습니다." << endl;
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

		cout << "<영수증>" << endl;
		cout << "==============================================" << endl;
		cout << "성훈이네 라면가게" << endl;
		cout << "----------------------------------------------" << endl;
		cout << "날짜 : " << 1900 + timeinfo->tm_year << "-" << 1 + timeinfo->tm_mon << "-" << timeinfo->tm_mday << " " << timeinfo->tm_hour << ":" << timeinfo->tm_min << endl;
		cout << "----------------------------------------------" << endl;
		cout << "주문번호 : " << pOrderList->Count-1 << "번 " << endl;
		cout << "----------------------------------------------" << endl;
		cout << "메뉴\t\t수량\t금액" << endl << endl;
		cout << "----------------------------------------------" << endl;

		for (unsigned int i = 0; i < (pOrder->Count); i++) {
			pOrderItem = pOrder->GetObject(i);
			cout << " ->     " << pOrderItem->Name << "\t\t" << pOrderItem->Count << "\t" << pOrderItem->Calculate() << endl;
			sum += pOrderItem->Calculate();
		}

		pPay = pPayList->GetPay((pPayList->Count) - 1);
		pPayItem = pPay->GetPayment(0); // 항상 0번째 자리에 있으므로

		cout << "----------------------------------------------" << endl;
		cout << "합계\t\t\t\t\t" << sum << "원" << endl << endl;
		cout << "----------------------------------------------" << endl;
		cout << "결제 수단\t\t\t" << pPayItem->Name << endl << endl;
		is_printed = 1; // 출력 완료 상태로 전환
		return;
	}
	else {
		cout << "출력할 주문이 없습니다." << endl;
		cout << endl << "홈 화면으로 돌아갑니다." << endl << endl;
		return;
	}
}