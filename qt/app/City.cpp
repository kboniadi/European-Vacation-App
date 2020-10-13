#include "City.h"

// Constructor
City::City()
{
    _name = "";
	_foods.clear();
}

// Destructor
City::~City() = default;

// Accessor: Get name of city
QString City::GetName() const
{
    return _name;
}

// Mutator: Alter/set city name
void City::SetName(const QString &name)
{
    _name = name;
}

// Accessor: Get food at this index of associated city
Food City::GetFoodAt(int index) const
{
	return _foods.at(index);
}

// Accessor: Get food name at this index of city
QString City::GetFoodNameAt(int index) const
{
	return _foods.at(index).GetName();
}

// Get food price at this index
float City::GetFoodPriceAt(int index) const
{
	return _foods.at(index).GetPrice();
}

// Get food price at this index
int City::GetFoodQtyAt(int index) const
{
	return _foods.at(index).GetQty();
}

// Set food qty at this index
void City::SetFoodQtyAt(int index, int qty)
{
	_foods[index].SetQty(qty);
}

// Mutator: Alter/set food list
void City::AddFood(const Food &item)
{
	_foods.push_back(item);
}

// Mutator: Alter/set food list
void City::RemoveFoodAt(int index)
{
    _foods.removeAt(index);
}



int City::GetFoodListSize() const
{
	return _foods.size();
}
