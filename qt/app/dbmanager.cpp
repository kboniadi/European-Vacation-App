#include "dbmanager.h"
#include <QFileDialog>

DBManager::DBManager(QWidget *parent)
	: QWidget{parent}, QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))
{
	setDatabaseName(QDir::currentPath() + "/Data.db");

	if (!open()) {
		qDebug() << "Connection to database failed";
	} else {
		qDebug() << "Connection to database succedded";
	}
}

DBManager::~DBManager()
{
	if (open()) {
		qDebug() << "Connection to database has been closed";
		QSqlDatabase::close();
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

void DBManager::ImportCities()
{
	QString startCity, endCity, distance;
	QString filter = "CSV file (*.csv)";
	QStringList cities;
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
													QDir::homePath(), filter);
	QFile file(fileName);

	getCities(cities);

	if (!file.open(QFile::ReadOnly)) {
			qDebug() << "error openning the file";
	} else {
		qDebug() << "file opened";
		QTextStream ss(&file);
		QStringList list;

		while (!ss.atEnd()) {
			QString line = ss.readLine();
			list = line.split(",");

			if (!cities.contains(list[0])) {
				query.prepare("INSERT INTO Parent(city) VALUES(:city)");
				query.bindValue(":city", list[0]);
				if (!query.exec()) {
					qDebug() << "Query didn't execute properly";
					return;
				}
				query.finish();
				getCities(cities);
			}

			query.prepare("SELECT id FROM Parent WHERE city = :city");
			query.bindValue(":city", list[0]);
			if (!query.exec()) {
				qDebug() << "Query didn't execute properly";
				return;
			}
			query.first();
			int id = query.value(0).toInt();

			query.prepare("INSERT INTO Distance(id, endCity, distance) "
						  "VALUES(:id, :endCity, :distance)");
			query.bindValue(":id", id);
			query.bindValue(":endCity", list[1]);
			query.bindValue(":distance", list[2]);
			if (!query.exec())
				qDebug() << "Query didn't execute properly";
			query.finish();
		}
	}
}

void DBManager::updateFoodPrice(const QString &foodName, const QString &price)
{
	query.prepare("UPDATE Food SET price = :price WHERE Food.food = :foodName");
	query.bindValue(":price", price);
	query.bindValue(":foodName", foodName);
	if (!query.exec())
		qDebug() << "Query didn't execute properly";
	query.finish();
}

void DBManager::deleteFood(const QString &foodName)
{
	query.prepare("DELETE FROM Food WHERE Food.food = :foodName");
	query.bindValue(":foodName", foodName);
	if (!query.exec())
		qDebug() << "Query didn't execute properly";
	query.finish();

}

void DBManager::cityToFoodNames(const QString &city, QVector<QString> &foods)
{
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

void DBManager::getCities(QStringList &cities)
{
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



