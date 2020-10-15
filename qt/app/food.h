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
     * @brief Mutator: Alter/set Food object's name attribute
     * @param name; Name to set
     */
    void SetName(const QString &name);

    /*!
     * @brief Accessor: Get price of food object
     * @return Price attribute of Food object
     */
    float GetPrice() const;

    /*!
     * @brief Mutator: Alter/set Food object's price attribute
     * @param price; Price to set
     */
	void SetPrice(float price);

    /*!
     * @brief Accessor: Get quantity of food object
     * @return Quantity attribute of Food object
     */
    int GetQty() const;

    /*!
     * @brief Mutator: Alter/set Food object's quantity attribute
     * @param qty; Quantity to set
     */
	void SetQty(int qty);

    /*!
     * @brief Default Food object constructor
     */
    Food();

    /*!
     * @brief Destructor
     */
	~Food() = default;
private:
    QString _name; /// Name of food object
    float _price;  /// Price of food object
    int _qty;      /// Quantity of food object
};

#endif // FOOD_H
