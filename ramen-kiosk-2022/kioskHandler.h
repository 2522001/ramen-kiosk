#pragma once

#include "orderList.h"
#include "payList.h"
#include "revenueManager.h"

class OrderCategory
{
	private:
		bool bPrint;
		bool mode; // ������ ��� 0, ������ ��� 1
		bool isPaid; // ���� �ʿ� 0, ���� �Ϸ� 1
		bool isPrinted; // ��� �ʿ� 0, ��� �Ϸ� 1
		
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

