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
 * stored in the database
 */
class City;

class DBManager: public QWidget, public QSqlDatabase {
	Q_OBJECT;
public:
	/*!
     * @brief Creates one instance of the database
     * @return Pointer the the instance of the database class
	 */
	static DBManager* instance();

	/*!
     * @brief Deleted copy constructor
	 */
	DBManager(const DBManager&) = delete;

	/*!
     * @brief Deleted copy assignment
	 */
	DBManager& operator=(const DBManager&) = delete;

	/*!
     * @brief AddFood items to the database
     * @param city; Name of City in which Food will be added
     * @param food; Name of the Food item to be added
     * @param price; Price of Food item to be added
	 */
    void AddFood(const QString &city, const QString &food, const QString &price);

	/*!
     * @brief Imports list of new cities from file
     * @param parent; Access to QWidget class
	 */
	void ImportCities(QWidget *parent = nullptr);

	/*!
     * @brief Updates food price in database
     * @param foodName; Name of food to be updated
     * @param price; New price of food item
	 */
	void UpdateFoodPrice(const QString &foodName, const QString &price);

	/*!
     * @brief Deletes food listing from database
     * @param foodName; Name of food to be deleted
	 */
	void DeleteFood(const QString &foodName);

	/*!
     * @brief Populates QStringList with food items for a particular city
     * @param city; Name of city containing traditional food items
     * @param foods; List of food items to be added
	 */
	void CityToFoodNames(const QString &city, QStringList &foods);

	/*!
     * @brief Will return price values for food item input
     * @param food; Name of food whos price is desired
     * @return Price for the passed in food item
	 */
	QString FoodNameToPrice(const QString &food);

	/*!
     * @brief Will return all cities in database
     * @param cities; Container that holds all the cities in database
	 */
	void GetCities(QStringList &cities);

	/*!
     * @brief Will return distance between two cities
     * @param city1; Name of origin city
     * @param city2; Name of destination city
     * @return Distance between two cities
	 */
	int GetDistances(const QString &city1, const QString &city2);

    /*!
     * @brief Populates Food items for list of given cities
     * @param cities; List of Cities that requires population of food items
     */
	void CreateShoppingList(QVector<City>* cities);

    /*!
     * @brief Populates data necessary for cities table to show cities and
     * distances from Berlin
     * @param cityNames; List of city names to be populated
     * @param distancesFromBerlin; List of distances from Berlin
     */
	void GetCitiesTable(QStringList *cityNames, QVector<int>* distancesFromBerlin);

    /*!
     * @brief Will validate login credentials for administrator access
     * @param username; User's username inputs
     * @param password; User's password input
     * @return Success or failure of login
     */
    bool LogIn(const QString &username, const QString &password);

private:
    QSqlQuery query;	/// Generic reusable query

	/*!
	 * @brief DBManager (private)
     * @param parent; Linked to QWidget class
	 */
	explicit DBManager(QWidget *parent = nullptr);

	/*!
     * @brief Destructor
	 */
	~DBManager();
};

#endif // DBMANAGER_H
