#include "City.h"
#include "food.h"

// Constructor
City::City()
{
    _name = "";
    _foods = new QVector<Food>;
}

// Destructor
City::~City()
{
}

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
Food City::GetFoodAt(const int &index) const
{
    return _foods->at(index);
}

// Accessor: Get food name at this index of city
QString City::GetFoodNameAt(const int &index) const
{
    return _foods->at(index).GetName();
}

// Get food price at this index
float City::GetFoodPriceAt(const int &index) const
{
    return _foods->at(index).GetPrice();
}

// Get food price at this index
int City::GetFoodQtyAt(const int &index) const
{
    return _foods->at(index).GetQty();
}

// Set food qty at this index
void City::SetFoodQtyAt(const int &index, const int &qty)
{
    _foods->operator[](index).SetQty(qty);
}

// Mutator: Alter/set food list
void City::AddFood(Food &item)
{
    _foods->push_back(item);
}

// Mutator: Alter/set food list
void City::RemoveFoodAt(const int &index) const
{
    _foods->removeAt(index);
}



int City::GetFoodListSize() const
{
    return _foods->size();
}

void City::DestroyCity()
{
    delete _foods;
}
