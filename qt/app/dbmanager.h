#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QDir>
#include <QString>
#include <QVector>
#include <QDebug>

class DBManager {
public:
	static DBManager* instance();
	DBManager(const DBManager&) = delete;
	DBManager& operator=(const DBManager&) = delete;
	void addFood(const QString &city, const QString &food,
				 const QString &price);
//	void ImportCities();
	void updateFoodPrice(const QString &foodName, const QString &price);
	void deleteFood(const QString &foodName);
//	void CreateTrip(const QVector<QString>&);
	void cityToFoodNames(const QString &city, QVector<QString> &foods);
	QString foodNameToPrice(const QString &food);
	void getCities(QVector<QString> &cities);
	int getDistances(const QString &city1, const QString &city2);
//	void getParisTripCities(QVector<QString>&);
//	void getBerlinTripCities(QVector<QString>&);
//	void getCustomTripCities(QVector<QString>&);
private:
	DBManager();
	~DBManager();
	QSqlDatabase db;
};

#endif // DBMANAGER_H
