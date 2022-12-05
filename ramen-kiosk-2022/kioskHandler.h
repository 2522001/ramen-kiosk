#pragma once

#include "OrderList.h"
#include "PayList.h"
#include "RevenueManager.h"

class KioskHandler
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
		KioskHandler(const OrderPreset& orderItem, OrderList* pOrderList, const PayPreset& payItem, PayList* pPayList, RevenueManager* pRevManager);

		bool Run(void);
};

