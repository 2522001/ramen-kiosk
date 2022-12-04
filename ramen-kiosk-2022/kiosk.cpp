#include <iostream>
#include "kiosk.h"

Kiosk::Kiosk(void) : handle(item, &orderList, payItem, &payList, &revManager)
{
	// 라면 종류
	item.AddObject(Object("일반라면", 3000, 1));
	item.AddObject(Object("순두부라면", 3700, 1));
	item.AddObject(Object("떡라면", 3300, 1));
	item.AddObject(Object("만두라면", 3500, 1));
	item.AddObject(Object("치즈라면", 3200, 1));

	// 라면 옵션1: 맵기 단계
	item.AddObject(Object("덜맵게", 0, 1));
	item.AddObject(Object("기본맵기", 0, 1));
	item.AddObject(Object("더맵게", 0, 1));

	// 라면 옵션2: 익힘 단계
	item.AddObject(Object("꼬들하게", 0, 1));
	item.AddObject(Object("기본익힘", 0, 1));
	item.AddObject(Object("퍼지게", 0, 1));

	// 음료
	item.AddObject(Object("콜라", 1500, 1));
	item.AddObject(Object("사이다", 1500, 1));

	// 반찬
	item.AddObject(Object("단무지", 500, 1));
	item.AddObject(Object("김치", 1500, 1));

	// 세트 메뉴
	item.AddObject(Object("세트 메뉴 1번", 7500, 1));
	item.AddObject(Object("세트 메뉴 2번", 5000, 1));

	// 결제수단
	payItem.AddPayment(Payment("카드"));
	payItem.AddPayment(Payment("네이버페이"));
	payItem.AddPayment(Payment("카카오페이"));
}

int Kiosk::Run(void)
{
	using namespace std;
	cout << "( ＾◡＾)っ ♡♡♡♡♡성훈이네 라면가게♡♡♡♡♡ (＾◡＾ )っ" << endl << endl;

	while (handle.Run());

	return 0;
}

