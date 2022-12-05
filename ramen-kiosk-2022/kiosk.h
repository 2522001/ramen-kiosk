#pragma once

#include "KioskHandler.h"
#include "OrderList.h"
#include "Pay.h"
#include "RevenueManager.h"

class Kiosk
{
private:
	KioskHandler handle; // kiosk_handler
	OrderPreset orderItem; // preset
	OrderList orderList;
	PayPreset payItem;
	PayList payList;
	RevenueManager revManager;

public:
	Kiosk(void);
	int Run(void);
};

