#ifndef CITY_H
#define CITY_H
#include <QString>
#include <QStringList>
#include <QVector>

class Food;

class City
{
public:
    // Constructor - Note: will set _foods to nullptr
    City();

    // Accessor: Get name of city
    QString GetName() const;
    // Mutator: Alter/set city name
    void SetName(const QString &name);

    // Accessor: Get food at index in associated with city
    Food GetFoodAt(const int &index) const;

    // Get food name at this index
    QString GetFoodNameAt(const int &index) const;

    // Get food price at this index
    float GetFoodPriceAt(const int &index) const;

    // Get food qty at this index
    int GetFoodQtyAt(const int &index) const;

    // Set food qty at this index
    void SetFoodQtyAt(const int &index, const int &qty);

    // Accessor: Get size of food list
    int GetFoodListSize() const;

    // Mutator: Alter/set food list
    void AddFood(Food &item);

    // Mutator: Alter/set food list
    void RemoveFoodAt(const int &index) const;

    // Destroy City Object
    void DestroyCity();

    // Destructor
    ~City();

private:
    QString _name;          // Name of city
    QVector<Food>* _foods;  // List of foods associated with city
};

#endif // CITY_H
