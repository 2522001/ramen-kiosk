#include "payItem.h"

PayItem::PayItem(const std::string& name) : name(name)
{

}

PayItem::PayItem(const PayItem& copy) : name(copy.name), Name(name)
{

}