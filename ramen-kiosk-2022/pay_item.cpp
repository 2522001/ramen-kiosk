#include "pay_item.h"

Payment::Payment(const std::string& name) : name(name)
{

}

Payment::Payment(const Payment& copy) : name(copy.name), Name(name)
{

}