#include "dbmanager.h"
#include "City.h"
#include "food.h"
#include <QFileDialog>
#include <QProgressDialog>

DBManager::DBManager(QWidget *parent)
	: QWidget{parent}, QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))
{
	setDatabaseName(QDir::currentPath() + "/Data.db");

	if (!open()) {
		qDebug() << "Connection to database failed";
	} else {
        qDebug() << "Connection to database succeeded";
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
	// creates one and only one instance of the database
	static DBManager instance;
	return &instance;
}

void DBManager::AddFood(const QString &city, const QString &food,
						const QString &price)
{
	// finds and stores the id associated with the city name
	query.prepare("SELECT id FROM cities WHERE cityNames = :city");
	query.bindValue(":city", city);
	if (!query.exec()) {
		qDebug() << "DBManager::AddFood() : query failed";
		return;
	}
	query.first();
	int id = query.value(0).toInt();

	// using the obtained id, a new food item and price is INSERTED
	query.prepare("INSERT INTO food(id, foodNames, price) "
				  "VALUES(:id, :food, :price)");
	query.bindValue(":id", id);
	query.bindValue(":food", food);
	query.bindValue(":price", price);
	if (!query.exec())
		qDebug() << "DBManager::AddFood() : query failed";
	query.finish();
}

void DBManager::ImportCities(QWidget *parent)
{
	QString startCity, endCity, distance;
	QString filter = "CSV file (*.csv)";
	QStringList cities;
	// opens system file directory in your home path
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
													QDir::homePath(), filter);
	// needed to iterate through file...similar to fstream
	QFile file(fileName);

	// populates cities with all the cities in the DB
	GetCities(cities);

	// loading bar beginning logic to mask slow query speeds
	// takes a QWidget pointer for window positioning purposes
	QProgressDialog progress("Updating db...", "Cancel", 0, 46, parent);
	progress.setWindowModality(Qt::WindowModal);
	progress.setCancelButton(0);
	progress.setWindowTitle("Loader");
	int count = 0;
	progress.setRange(count, 52);
	progress.setMinimumDuration(count);
	// loading bar increases linearly with count
//	progress.setValue(count);

//	QTime start = QTime::currentTime();

	if (!file.open(QFile::ReadOnly)) {
            qDebug() << "DBManager::ImportCities() : error opening the file";
	} else {
		qDebug() << "file opened";
		QTextStream ss(&file);
		QStringList list;
		bool foodStarted = false;

		while (!ss.atEnd()) {
			QString line = ss.readLine();
			if (line == "//Food") {
				foodStarted = true;
				line = ss.readLine();
			}
			// parses each line in the csv into a QStringList
			list = line.split(",");

			// only insert if the city is unique
			if (!cities.contains(list[0])) {
				query.prepare("INSERT INTO cities(cityNames) VALUES(:city)");
				query.bindValue(":city", list[0]);
				if (!query.exec()) {
					qDebug() << "DBManager::ImportCities() : error executing query";
					return;
				}
				// re-populates cities with updated city list
				GetCities(cities);
			}

			// finds and stores the id associated with the city name
			query.prepare("SELECT id FROM cities WHERE cityNames = :city");
			query.bindValue(":city", list[0]);
			if (!query.exec()) {
				qDebug() << "DBManager::ImportCities() : error executing query(city data)";
				return;
			}
			query.first();
			int id = query.value(0).toInt();

			if (foodStarted) {
				query.prepare("INSERT INTO food(id, foodNames, price) "
							  "VALUES(:id, :food, :price)");
				query.bindValue(":id", id);
				query.bindValue(":food", list[1]);
				query.bindValue(":price", list[2]);
			} else {
				// insert distance and endCity data into DB
				query.prepare("INSERT INTO distance(id, endCity, distances) "
							  "VALUES(:id, :endCity, :distance)");
				query.bindValue(":id", id);
				query.bindValue(":endCity", list[1]);
				query.bindValue(":distance", list[2]);
			}

			if (!query.exec())
				qDebug() << "DBManager::ImportCities() : error executing query";

			// update progress bar
			progress.setValue(++count);
		}
		query.finish();
	}
//	QTime end = QTime::currentTime();
//	qDebug() << "function took: " << start.msecsTo(end) / 1000.0 << " sec";
}

void DBManager::UpdateFoodPrice(const QString &foodName, const QString &price)
{
	query.prepare("UPDATE food SET price = :price WHERE food.foodNames = :foodName");
	query.bindValue(":price", price);
	query.bindValue(":foodName", foodName);
	if (!query.exec())
		qDebug() << "DBManager::UpdateFoodPrice() : query failed";
	query.finish();
}

void DBManager::DeleteFood(const QString &foodName)
{
	query.prepare("DELETE FROM food WHERE food.foodNames = :foodName");
	query.bindValue(":foodName", foodName);
	if (!query.exec())
		qDebug() << "DBManager::DeleteFood() : query failed";
	query.finish();

}

void DBManager::CityToFoodNames(const QString &city, QStringList &foods)
{
	query.prepare("SELECT foodNames FROM food, cities WHERE cities.cityNames = "
				  ":city AND cities.id = food.id");
	query.bindValue(":city", city);
	if (query.exec()) {
		while (query.next())
			foods.push_back(query.value(0).toString());
		query.finish();
	} else {
		qDebug() << "DBManager::CityToFoodNames() : query failed";
	}
}

QString DBManager::FoodNameToPrice(const QString &food)
{
	query.prepare("SELECT price FROM food WHERE food.foodNames = :food");
	query.bindValue(":food", food);
	if (query.exec()) {
		query.first();
		return query.value(0).toString();
	} else {
		qDebug() << "DBManager::FoodNameToPrice() : query failed";
	}
	return QString("Error");
}

void DBManager::GetCities(QStringList &cities)
{
	query.prepare("SELECT cityNames FROM cities");
	if (query.exec()) {
		while (query.next())
			cities.push_back(query.value(0).toString());
		query.finish();
	} else {
		qDebug() << "DBManager::GetCities() : query failed";
	}
}

int DBManager::GetDistances(const QString &city1, const QString &city2)
{
	query.prepare("SELECT distances FROM distance, cities WHERE "
				  "cities.cityNames = :city1 AND cities.id = distance.id AND "
				  "endCity = :city2");

	query.bindValue(":city1", city1);
	query.bindValue(":city2", city2);

	if (query.exec()) {
		query.first();
		return query.value(0).toInt();
	} else {
		qDebug() << "DBManager::GetDistances() : query failed";
	}
	// can indicate that city name is wrong or not part of DB
	return -1;
}


void DBManager::CreateShoppingList(QVector<City>* cities)
{
    // Prep general query
	query.prepare("SELECT food.foodNames, food.price FROM cities, food WHERE "
				  "citynames = :cityName and cities.id = food.id;");

    // Run query in a loop
    for(int index = 0; index < cities->size(); index++)
    {
        // Bind value
        query.bindValue(":cityName", cities->at(index).GetName());

        // Execute query
        if(query.exec())
        {
            // While food exists in DB for this specific city
            while(query.next())
            {
                // Create a food item
                Food temp;

                // Populate it
                temp.SetName(query.value(0).toString());
                temp.SetPrice(query.value(1).toFloat());

                // Add it to the object's food vector
                cities->operator[](index).AddFood(temp);
            }
        }
        else
        {
            qDebug() << "Query didn't execute properly";
        }
    }
}

void DBManager::GetCitiesTable(QStringList* cityNames, QVector<int>* distancesFromBerlin)
{
	query.prepare("SELECT cities.citynames, distance.distances FROM cities, "
				  "distance WHERE distance.endcity = 'Berlin' AND cities.id = "
				  "distance.id;");

    if(query.exec())
    {
        QString cityName;
        int distance;
        while(query.next())
        {
            // Load objects
            cityName = query.value(0).toString();
            distance = query.value(1).toInt();

            cityNames->append(cityName);
            distancesFromBerlin->push_back(distance);

            qDebug() << "City added: " << cityName;
            qDebug() << "Distance: " << distance;
        }
    }
    else
    {
        qDebug() << "GetCitiesTable query didn't execute properly";
    }
}
