#ifndef CITY_H
#define CITY_H
#include <QString>
#include <QStringList>

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

    // Accessor: Get food list associated with city
    QVector<Food>* GetFoods() const;
    // Mutator: Alter/set food list
    void SetFoods(QVector<Food>* &foodList);

    // Destroy City Object
    void DestroyCity();

private:
    QString _name;          // Name of city
    QVector<Food>* _foods;  // List of foods associated with city
};

#endif // CITY_H
