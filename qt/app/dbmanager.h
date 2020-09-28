#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QDir>
#include <QString>
#include <QVector>
#include <QDebug>

class DBManager: public QWidget, public QSqlDatabase {
	Q_OBJECT;
public:
	static DBManager* instance();
	DBManager(const DBManager&) = delete;
	DBManager& operator=(const DBManager&) = delete;
	void AddFood(const QString &city, const QString &food,
				 const QString &price);
	void ImportCities();
	void UpdateFoodPrice(const QString &foodName, const QString &price);
	void DeleteFood(const QString &foodName);
//	void CreateTrip(const QVector<QString>&);
	void CityToFoodNames(const QString &city, QVector<QString> &foods);
	QString FoodNameToPrice(const QString &food);
	void GetCities(QStringList &cities);
	int GetDistances(const QString &city1, const QString &city2);
//	void getParisTripCities(QVector<QString>&);
//	void getBerlinTripCities(QVector<QString>&);
//	void getCustomTripCities(QVector<QString>&);

//  QVector<City>* CreateShoppingList(QVector<City>* cities);
private:
	QSqlQuery query;

	DBManager(QWidget *parent = nullptr);
	~DBManager();
};

#endif // DBMANAGER_H
