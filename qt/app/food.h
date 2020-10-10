#ifndef FOOD_H
#define FOOD_H

#include <QString>

class Food
{
public:
    // Accessor: Get name of food item
    QString GetName() const;
    // Mutator: Alter/set food item name
    void SetName(const QString &name);

    // Accessor: Get price of food item
    float GetPrice() const;
    // Mutator: Alter/set food item name
	void SetPrice(float price);

    // Accessor: Get quantity of purchased food item
    int GetQty() const;
    // Mutator: Alter/set quantity of purchased food item
	void SetQty(int qty);

    // Constructor
    Food();

private:
    QString _name;
    float _price;
    int _qty;
};

#endif // FOOD_H
