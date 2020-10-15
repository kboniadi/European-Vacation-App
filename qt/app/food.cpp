#include "food.h"

// Constructor
Food::Food():  _name{QString{}}, _price{0}, _qty{0} {}

// Accessor: Get name of food item
QString Food::GetName() const
{
    return _name;
}

// Mutator: Alter/set food item name
void Food::SetName(const QString &name)
{
    _name = name;
}

// Accessor: Get price of food item
float Food::GetPrice() const
{
    return _price;
}

// Mutator: Alter/set food item name
void Food::SetPrice(float price)
{
    _price = price;
}

// Accessor: Get quantity of purchased food item
int Food::GetQty() const
{
    return _qty;
}

// Mutator: Alter/set quantity of purchased food item
void Food::SetQty(int qty)
{
    _qty = qty;
}
