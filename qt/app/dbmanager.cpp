#include "dbmanager.h"

DBManager::DBManager()
{
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(QDir::currentPath() + "/Data.db");

	if (!db.open()) {
		qDebug() << "Connection to database failed";
	} else {
		qDebug() << "Connection to database succedded";
	}
}

DBManager::~DBManager()
{
	if (db.open()) {
		qDebug() << "Connection to database has been closed";
		db.close();
	}
}

DBManager* DBManager::instance()
{
	static DBManager instance;
	return &instance;
}

void DBManager::addFood(const QString &city, const QString &food,
						const QString &price)
{
	QSqlQuery query;
	query.prepare("SELECT id FROM Parent WHERE city = :city");
	query.bindValue(":city", city);
	if (!query.exec()) {
		qDebug() << "Query didn't execute properly";
		return;
	}
	query.first();
	int id = query.value(0).toInt();

	query.prepare("INSERT INTO Food(id, food, price) VALUES(:id, :food, :price)");
	query.bindValue(":id", id);
	query.bindValue(":food", food);
	query.bindValue(":price", price);
	if (!query.exec())
		qDebug() << "Query didn't execute properly";
	query.finish();

}

void DBManager::updateFoodPrice(const QString &foodName, const QString &price)
{
	QSqlQuery query;
	query.prepare("UPDATE Food SET price = :price WHERE Food.food = :foodName");
	query.bindValue(":price", price);
	query.bindValue(":foodName", foodName);
	if (!query.exec())
		qDebug() << "Query didn't execute properly";
	query.finish();
}

void DBManager::deleteFood(const QString &foodName)
{
	QSqlQuery query;
	query.prepare("DELETE FROM Food WHERE Food.food = :foodName");
	query.bindValue(":foodName", foodName);
	if (!query.exec())
		qDebug() << "Query didn't execute properly";
	query.finish();

}

void DBManager::cityToFoodNames(const QString &city, QVector<QString> &foods)
{
	QSqlQuery query;
	query.prepare("SELECT food FROM Food, Parent WHERE Parent.city = :city AND "
				  "Parent.id = Food.id");
	query.bindValue(":city", city);
	if (query.exec()) {
		while (query.next())
			foods.push_back(query.value(0).toString());
		query.finish();
	} else {
		qDebug() << "Query didn't execute properly";
	}
}

QString DBManager::foodNameToPrice(const QString &food)
{

	QSqlQuery query;
	query.prepare("SELECT price FROM Food WHERE Food.food = :food");
	query.bindValue(":food", food);
	if (query.exec()) {
		query.first();
		return query.value(0).toString();
	} else {
		qDebug() << "Query didn't execute properly";
	}
	return QString("Error");
}

void DBManager::getCities(QVector<QString> &cities)
{
	QSqlQuery query;
	query.prepare("SELECT city FROM Parent");
	if (query.exec()) {
		while (query.next())
			cities.push_back(query.value(0).toString());
		query.finish();
	} else {
		qDebug() << "Query didn't execute properly";
	}
}

int DBManager::getDistances(const QString &city1, const QString &city2)
{
	QSqlQuery query;

	query.prepare("SELECT distance FROM Distance, Parent WHERE "
				  "Parent.city = :city1 AND Parent.id = Distance.id AND "
				  "endCity = :city2");

	query.bindValue(":city1", city1);
	query.bindValue(":city2", city2);

	if (query.exec()) {
		query.first();
		return query.value(0).toInt();
	} else {
		qDebug() << "Query didn't execute properly";
	}
	return -1;
}

