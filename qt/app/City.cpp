#include "City.h"
#include "food.h"

// Constructor
City::City()
{
    _name = "";
    _foods = nullptr;
}

// Destructor
City::~City()
{
    delete _foods;
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

// Accessor: Get food list associated with city
QVector<Food>* City::GetFoods() const
{
    return _foods;
}

// Mutator: Alter/set food list
void City::SetFoods(QVector<Food>* &foodList)
{
    _foods = foodList;
}

void City::DestroyCity()
{
    delete _foods;
}
