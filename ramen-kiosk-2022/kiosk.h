#pragma once

#include "kiosk_handler.h"
#include "cart.h"
#include "pay.h"
#include "revenue_manager.h"

class Kiosk
{
private:
	OrderCategory handle; // kiosk_handler
	MenuItem item; // preset
	OrderList orderList;
	PayPreset payItem;
	PayList payList;
	RevenueManager revManager;

public:
	Kiosk(void);
	int Run(void);
};

