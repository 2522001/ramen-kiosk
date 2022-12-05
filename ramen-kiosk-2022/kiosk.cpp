#include <iostream>
#include "Kiosk.h"

Kiosk::Kiosk(void) : handle(orderItem, &orderList, payItem, &payList, &revManager)
{
	// 라면 종류
	orderItem.AddOrderItem(OrderItem("일반라면", 3000, 1));
	orderItem.AddOrderItem(OrderItem("순두부라면", 3700, 1));
	orderItem.AddOrderItem(OrderItem("떡라면", 3300, 1));
	orderItem.AddOrderItem(OrderItem("만두라면", 3500, 1));
	orderItem.AddOrderItem(OrderItem("치즈라면", 3200, 1));

	// 라면 옵션1: 맵기 단계
	orderItem.AddOrderItem(OrderItem("덜맵게", 0, 1));
	orderItem.AddOrderItem(OrderItem("기본맵기", 0, 1));
	orderItem.AddOrderItem(OrderItem("더맵게", 0, 1));

	// 라면 옵션2: 익힘 단계
	orderItem.AddOrderItem(OrderItem("꼬들하게", 0, 1));
	orderItem.AddOrderItem(OrderItem("기본익힘", 0, 1));
	orderItem.AddOrderItem(OrderItem("퍼지게", 0, 1));

	// 음료
	orderItem.AddOrderItem(OrderItem("콜라", 1500, 1));
	orderItem.AddOrderItem(OrderItem("사이다", 1500, 1));

	// 반찬
	orderItem.AddOrderItem(OrderItem("단무지", 500, 1));
	orderItem.AddOrderItem(OrderItem("김치", 1500, 1));

	// 세트 메뉴
	orderItem.AddOrderItem(OrderItem("세트 메뉴 1번", 7500, 1));
	orderItem.AddOrderItem(OrderItem("세트 메뉴 2번", 5000, 1));

	// 결제수단
	payItem.AddPayItem(PayItem("카드"));
	payItem.AddPayItem(PayItem("네이버페이"));
	payItem.AddPayItem(PayItem("카카오페이"));
}

int Kiosk::Run(void)
{
	using namespace std;
	cout << "♡성훈님과 제자들의 라면가게♡" << endl << endl;

	while (handle.Run());

	return 0;
}

