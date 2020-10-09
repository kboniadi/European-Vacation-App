#include "City.h"

// Constructor
City::City()
{
    _name = "";
    _foods = nullptr;
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
QStringList* City::GetFoods() const
{
    return _foods;
}

// Mutator: Alter/set food list
void City::SetFoods(QStringList* &foodList)
{
    _foods = foodList;
}
