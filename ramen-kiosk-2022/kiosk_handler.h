#pragma once

#include "cart.h"
#include "pay_list.h"
#include "revenue_manager.h"

class OrderCategory
{
	private:
		bool bPrint;
		bool mode; // ������ ��� 0, ������ ��� 1
		bool is_paid; // ���� �ʿ� 0, ���� �Ϸ� 1
		
		const MenuItem& item;
		OrderList* pOrderList;
		const PayPreset& payItem;
		PayList* pPayList;
		RevenueManager* pRevManager;

		bool Settings(void);
		void PrintOrder(void);
		void AddOrder(void);
		void EditOrder(void);
		void AddPayment(void);

	public:
		OrderCategory(const MenuItem& item, OrderList* pOrderList, const PayPreset& payItem, PayList* pPayList, RevenueManager* pRevManager);

		bool Run(void);
};

