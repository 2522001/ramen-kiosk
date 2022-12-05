#pragma once

#include "orderList.h"
#include "payList.h"
#include "revenueManager.h"

class OrderCategory
{
	private:
		bool bPrint;
		bool mode; // 구매자 모드 0, 관리자 모드 1
		bool isPaid; // 결제 필요 0, 결제 완료 1
		bool isPrinted; // 출력 필요 0, 출력 완료 1
		
		const OrderPreset& orderItem;
		OrderList* pOrderList;
		const PayPreset& payItem;
		PayList* pPayList;
		RevenueManager* pRevManager;

		bool Settings(void);
		void NewOrder(void);
		void CheckOrder(void);
		void EditOrder(void);
		void NewPay(void);
		void PrintReceipt(void);

	public:
		OrderCategory(const OrderPreset& orderItem, OrderList* pOrderList, const PayPreset& payItem, PayList* pPayList, RevenueManager* pRevManager);

		bool Run(void);
};

