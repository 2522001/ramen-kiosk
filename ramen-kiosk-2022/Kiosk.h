#pragma once

#include "KioskHandler.h"
#include "OrderList.h"
#include "PayList.h"
#include "RevenueManager.h"

class Kiosk
{
private:
	KioskHandler handle;
	OrderPreset orderItem;
	OrderList orderList;
	PayPreset payItem;
	PayList payList;
	RevenueManager revManager;

public:
	Kiosk(void);
	int Run(void);
};

