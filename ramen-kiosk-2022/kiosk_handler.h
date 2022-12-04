#pragma once

#include "order_list.h"
#include "pay_list.h"
#include "revenue_manager.h"

class OrderCategory
{
	private:
		bool bPrint;
		bool mode; // ������ ��� 0, ������ ��� 1
		bool is_paid; // ���� �ʿ� 0, ���� �Ϸ� 1
		bool is_printed; // ��� �ʿ� 0, ��� �Ϸ� 1
		
		const MenuItem& item;
		OrderList* pOrderList;
		const PayPreset& payItem;
		PayList* pPayList;
		RevenueManager* pRevManager;

		bool Settings(void);
		void PrintOrder(void);
		void AddOrder(void);
		void EditOrder(void);
		void AddPay(void);
		void PrintReceipt(void);

	public:
		OrderCategory(const MenuItem& item, OrderList* pOrderList, const PayPreset& payItem, PayList* pPayList, RevenueManager* pRevManager);

		bool Run(void);
};

