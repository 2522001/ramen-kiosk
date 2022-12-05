#pragma once

#include "kioskHandler.h"
#include "orderList.h"
#include "pay.h"
#include "revenueManager.h"

class Kiosk
{
private:
	OrderCategory handle; // kiosk_handler
	OrderPreset orderItem; // preset
	OrderList orderList;
	PayPreset payItem;
	PayList payList;
	RevenueManager revManager;

public:
	Kiosk(void);
	int Run(void);
};

