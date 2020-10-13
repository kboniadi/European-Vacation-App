#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QTime>

/*!
 * @class DBManager
 * @brief The DBManager class manages core methods used to access the data
 * stored in the data base
 */
class City;

class DBManager: public QWidget, public QSqlDatabase {
	Q_OBJECT;
public:
	/*!
	 * @brief creats one instance of the data base
	 * @return pointer the the instance of the data base class
	 */
	static DBManager* instance();

	/*!
	 * @brief deleted copy constructor
	 */
	DBManager(const DBManager&) = delete;

	/*!
	 * @brief deleted copy assignment
	 */
	DBManager& operator=(const DBManager&) = delete;

	/*!
	 * @brief AddFood items to the DB
	 * @param city; name of city your adding a food item to
	 * @param food; name of the item
	 * @param price; items cost
	 */
	void AddFood(const QString &city,
				 const QString &food,
				 const QString &price);

	/*!
	 * @brief ImportCities
	 * @param parent; access to QWidget class
	 */
	void ImportCities(QWidget *parent = nullptr);

	/*!
	 * @brief UpdateFoodPrice
	 * @param foodName;
	 * @param price;
	 */
	void UpdateFoodPrice(const QString &foodName, const QString &price);

	/*!
	 * @brief DeleteFood
	 * @param foodName
	 */
	void DeleteFood(const QString &foodName);

	/*!
	 * @brief CityToFoodNames populates QStringList type with food items for
	 * a particular city
	 * @param city; city name
	 * @param foods; food name
	 */
	void CityToFoodNames(const QString &city, QStringList &foods);

	/*!
	 * @brief FoodNameToPrice
	 * @param food; name of item
	 * @return price for the passed in food item
	 */
	QString FoodNameToPrice(const QString &food);

	/*!
	 * @brief GetCities
	 * @param cities; container that holds all the cities in DB
	 */
	void GetCities(QStringList &cities);

	/*!
	 * @brief GetDistances
	 * @param city1; name
	 * @param city2; name
	 * @return distance between two cities
	 */
	int GetDistances(const QString &city1, const QString &city2);

  void CreateShoppingList(QVector<City>* cities);

  void GetCitiesTable(QStringList *cityNames, QVector<int>* distancesFromBerlin);

  bool LogIn(const QString &username, const QString &password);

private:
	QSqlQuery query;	//!< used to query the database

	/*!
	 * @brief DBManager (private)
	 * @param parent; linked to QWidget class
	 */
	explicit DBManager(QWidget *parent = nullptr);

	/*!
	 * @brief deallocates any allocated memory
	 */
	~DBManager();
};

#endif // DBMANAGER_H
