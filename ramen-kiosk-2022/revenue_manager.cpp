#include "revenue_manager.h"

RevenueManager::RevenueManager(void) : today(0)
{

}

void RevenueManager::Calculate(unsigned int amount)
{
	today += amount;

	return;
}

