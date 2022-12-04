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
					pEditObj = pEditing->GetObject(i);
					pEditObj = new Object(pEditObj->Name, pEditObj->Price, pEditObj->Count);
				}
				if (pEditing->DeleteObject(*pEditObj)) { // object가 모두 삭제 되어 order가 비었다면
					pOrderList->DeleteOrder(pOrderList->Count - 1); // 해당 주문 주문리스트에서 삭제

					delete pEditObj;
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
			cin >> objName;

			if (objName == "0") {
				break;
			}

			pObj = item.GetObject(objName);
			if (pObj == 0) {
				cout << "해당 메뉴는 없습니다." << endl;
				continue;
			}


			// 라면 주문인 경우에만 맵기, 익힘 정도 선택 
			if (objName == "일반라면" || objName == "순두부라면" || objName == "떡라면" || objName == "만두라면" || objName == "치즈라면") {
				int ramenPrice = pObj->Price;
			ONE:
				cout << "> 맵기정도를 입력하세요: ";
				cin >> objSpicy;

				if (objSpicy == "0") {
					break;
				}

				pObj = item.GetObject(objSpicy);
				if (pObj == 0) {
					cout << "해당 맵기정도는 없습니다." << endl;
					goto ONE;
				}


			TWO:
				cout << "> 익힘정도를 입력하세요: ";
				cin >> objCooked;

				if (objCooked == "0") {
					break;
				}

				pObj = item.GetObject(objCooked);
				if (pObj == 0) {
					cout << "해당 익힘정도는 없습니다." << endl;
					goto TWO;
				}

				cout << "> 해당 메뉴를 몇개 주문하시겠습니까?: ";
				cin >> objCount;

				if (objCount == 0) {
					break;
				}

				
				pObj = new Object(objName, ramenPrice, objCount);


				pOrder->AddObject(*pObj);

			}
			else {
				cout << "> 해당 메뉴를 몇개 주문하시겠습니까?: ";
				cin >> objCount;

				if (objCount == 0) {
					break;
				}

				pObj = new Object(objName, pObj->Price, objCount);

				pOrder->AddObject(*pObj);
			}

			if (objName == "일반라면" || objName == "순두부라면" || objName == "떡라면" || objName == "만두라면" || objName == "치즈라면") {
				pObj = new Object(objSpicy, 0, 0);
				pOrder->AddObject(*pObj);

				pObj = new Object(objCooked, 0, 0);

				pOrder->AddObject(*pObj);

			}

			delete pObj;

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
	Object* pObj = 0;
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
				pObj = pOrder->GetObject(j);
				cout << " ->     " << pObj->Name << "   " << pObj->Count << "개        " << pObj->Calculate() << "원" << endl;
				sum += pObj->Calculate();
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
				pObj = pOrder->GetObject(j);
				cout << " ->     " << pObj->Name << "   " << pObj->Count << "개        " << pObj->Calculate() << "원" << endl;
				sum += pObj->Calculate();
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

	cout << endl << "주문을 수정합니다." << endl << endl;

	if (is_paid == 1) {
		cout << "주문이 없습니다." << endl << endl;
		return;
	}
	pEditing = pOrderList->GetOrder((pOrderList->Count) - 1);

	/* } else { // 관리자 모드: 결제 완료 상태의 모든 주문 리스트 불러오기
		if (pOrderList->Count == 0) {
			cout << "주문이 없습니다." << endl << endl;
			return;
		}
		cout << "> 수정할 주문 번호를 입력하십시오: ";
		cin >> index;

		if (index >= pOrderList->Count) {
			cout << "잘못된 주문번호 입니다." << endl << endl;
			return;
		}
		pEditing = pOrderList->GetOrder(index);
	}*/

	while (true) {
		cout << "> 수정 서식을 입력하십시오([메뉴] [개수] [추가/제거]): ";
		cin >> objName >> objCount >> behavior;

		if (objName == "0") {
			break;
		}

		if (behavior == "추가") {
			pEditObj = item.GetObject(objName);
			if (pEditObj == 0) {
				cout << "메뉴를 찾을 수 없습니다." << endl << endl;
				continue;
			}
			else {
				pEditObj = new Object(objName, pEditObj->Price, objCount);
				pEditing->AddObject(*pEditObj);
				delete pEditObj;
			}
		}
		else if (behavior == "제거") {
			pEditObj = pEditing->GetObject(objName);
			if (pEditObj == 0) {
				cout << "메뉴를 찾을 수 없습니다." << endl << endl;
				continue;
			}
			else {
				if (objName == "덜맵게" || objName == "기본맵기" || objName == "더맵게") {
					pEditObj = new Object(objName, pEditObj->Price, objCount);
					if (pEditing->DeleteObject(*pEditObj)) {
						pOrderList->DeleteOrder((pOrderList->Count) - 1);
						//is_paid = 1;
					}
					delete pEditObj;

					pEditObj = new Object("기본맵기", 0, 0);
					pEditing->AddObject(*pEditObj);
					delete pEditObj;

				}
				else if (objName == "꼬들하게" || objName == "기본익힘" || objName == "퍼지게") {
					pEditObj = new Object(objName, pEditObj->Price, objCount);
					if (pEditing->DeleteObject(*pEditObj)) {
						pOrderList->DeleteOrder((pOrderList->Count) - 1);
						//is_paid = 1;
					}
					delete pEditObj;

					pEditObj = new Object("기본익힘", 0, 0);
					pEditing->AddObject(*pEditObj);
					delete pEditObj;

				}
				else if (objName == "일반라면" || objName == "순두부라면" || objName == "떡라면" || objName == "만두라면" || objName == "치즈라면") {
					pEditObj = new Object(objName, pEditObj->Price, objCount);
					if (pEditing->DeleteObject(*pEditObj)) {
						pOrderList->DeleteOrder((pOrderList->Count) - 1);
						is_paid = 1;
					}
					delete pEditObj;

					pEditObj = pEditing->GetObject(objName);
					if (pEditObj == 0) {
						// 라면이 아예 0개로 제거되는 경우 옵션 삭제
						objSpicy1 = "덜맵게";
						pEditingSpicy1 = pOrderList->GetOrder((pOrderList->Count) - 1);
						pEditObjSpicy1 = pEditing->GetObject(objSpicy1);
						if (pEditObjSpicy1 == 0) {
							objSpicy2 = "기본맵기";
							pEditingSpicy2 = pOrderList->GetOrder((pOrderList->Count) - 1);
							pEditObjSpicy2 = pEditing->GetObject(objSpicy2);
							if (pEditObjSpicy2 == 0) {
								objSpicy3 = "더맵게";
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

						objCooked1 = "꼬들하게";
						pEditingCooked1 = pOrderList->GetOrder((pOrderList->Count) - 1);
						pEditObjCooked1 = pEditing->GetObject(objCooked1);
						if (pEditObjCooked1 == 0) {
							objCooked2 = "기본익힘";
							pEditingCooked2 = pOrderList->GetOrder((pOrderList->Count) - 1);
							pEditObjCooked2 = pEditing->GetObject(objCooked2);
							if (pEditObjCooked2 == 0) {
								objCooked3 = "퍼지게";
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
						is_paid = 1; // 해당 주문이 사라졌으므로 주문 완료 상태로 전환
					}
					delete pEditObj;
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
			pObj = pOrder->GetObject(i);
			cout << " ->     " << pObj->Name << "\t\t" << pObj->Count << "\t" << pObj->Calculate() << endl;
			sum += pObj->Calculate();
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