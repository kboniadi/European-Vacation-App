#ifndef CITY_H
#define CITY_H
#include <QString>
#include <QStringList>
#include <QVector>
#include "food.h"

/*!
 * @class City
 * @brief The City class is an object meant to represent city destinations
 */
class City
{
public:
    /*!
     * @brief Default City object constructor
     */
    City();

    /*!
     * @brief Parameterized City object constructor
     * @param city; name of city for object's name
     */
	City(QString city);

    /*!
     * @brief Accessor: Get name of city object
     * @return Name of city object
     */
    QString GetName() const;

    /*!
     * @brief Mutator: Alter/set city name
     * @param name; Name of city
     */
    void SetName(const QString &name);

    /*!
     * @brief Accessor: Return Food object at index in associated city
     * @param index; Position of item in vector
     * @return Food object at position desired
     */
	Food GetFoodAt(int index) const;

    /*!
     * @brief Accessor: Get Food object's name at index in associated city
     * @param index; Position of item in vector
     * @return Food object name at position desired
     */
	QString GetFoodNameAt(int index) const;

    /*!
     * @brief Accessor: Get Food object price at index in associated city
     * @param index; Position of item in vector
     * @return Food object price at position desired
     */
	float GetFoodPriceAt(int index) const;

    /*!
     * @brief Accessor: Get Food object quantity at index in associated city
     * @param index; Position of item in vector
     */
	int GetFoodQtyAt(int index) const;

    /*!
     * @brief Mutator: Alter/set Food object quantity at this index in City list
     * @param index; Position of Food object in list
     * @param qty; Quantity of Food object to set.
     */
	void SetFoodQtyAt(int index, int qty);

    /*!
     * @brief Accessor: Get size of city's Food object list
     * @return Size of Food object list
     */
    int GetFoodListSize() const;

    /*!
     * @brief Mutator: Add Food object to City object's food list.
     * @param item; Food object to add
     */
	void AddFood(const Food &item);

    /*!
     * @brief Mutator: Remove Food object from City object's food list.
     * @param index; Position of Food object in list to remove
     */
    void RemoveFoodAt(int index);


    /*!
     * @brief Destructor
     */
	~City() = default;

private:
    QString _name;          /// Name of city
    QVector<Food> _foods;   /// List of foods associated with city
};

#endif // CITY_H
