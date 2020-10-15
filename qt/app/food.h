#ifndef FOOD_H
#define FOOD_H

#include <QString>

/*!
 * @class Food
 * @brief The Food class is an object that represents the traditional food
 * items available in each city.
 */
class Food
{
public:
    /*!
     * @brief Accessor: Get name of food object
     * @return Name attribute of Food object
     */
    QString GetName() const;

    /*!
     * @brief Mutator: Alter/set Food object name attribute
     * @param name; Name to set
     */
    void SetName(const QString &name);

    /*!
     * @brief Accessor: Get price of food object
     * @return Price attribute of Food object
     */
    float GetPrice() const;

    // Mutator: Alter/set food item name
	void SetPrice(float price);

    // Accessor: Get quantity of purchased food item
    int GetQty() const;

    // Mutator: Alter/set quantity of purchased food item
	void SetQty(int qty);

    // Constructor
    Food();

	~Food() = default;
private:
    QString _name; /// Name of food object
    float _price;  /// Price of food object
    int _qty;      /// Quantity of food object
};

#endif // FOOD_H
