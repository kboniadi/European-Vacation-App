#ifndef CITY_H
#define CITY_H
#include <QString>
#include <QStringList>
#include <QVector>
#include "food.h"

class City
{
public:
    // Constructor - Note: will set _foods to nullptr
    City();
	City(QString city);

    // Accessor: Get name of city
    QString GetName() const;
    // Mutator: Alter/set city name
    void SetName(const QString &name);

    // Accessor: Get food at index in associated with city
	Food GetFoodAt(int index) const;

    // Get food name at this index
	QString GetFoodNameAt(int index) const;

    // Get food price at this index
	float GetFoodPriceAt(int index) const;

    // Get food qty at this index
	int GetFoodQtyAt(int index) const;

    // Set food qty at this index
	void SetFoodQtyAt(int index, int qty);

    // Accessor: Get size of food list
    int GetFoodListSize() const;

    // Mutator: Alter/set food list
	void AddFood(const Food &item);

    void RemoveFoodAt(int index);
    // Mutator: Alter/set food list
    // Destructor
	~City() = default;

private:
    QString _name;          // Name of city
	QVector<Food> _foods;  // List of foods associated with city
};

#endif // CITY_H
