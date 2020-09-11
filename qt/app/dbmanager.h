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
	void AddFood(QString& name, QString& price);
	void ImportCities();
	void ChangeFoodPrice(QString& foodName, float price);
	void DeleteFood(QString& foodName);
	void CreateTrip(const QVector<QString>&);
	void getCities(QVector<QString>&);
	void getDistances(QVector<QString>&);
	void getParisTripCities(QVector<QString>&);
	void getBerlinTripCities(QVector<QString>&);
	void getCustomTripCities(QVector<QString>&);
private:
	DBManager();
	~DBManager();
	QSqlDatabase db;
};

#endif // DBMANAGER_H
