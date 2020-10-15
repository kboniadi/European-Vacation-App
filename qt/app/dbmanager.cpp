#include "dbmanager.h"
#include "City.h"
#include "food.h"
#include <QFileDialog>
#include <QProgressDialog>

DBManager::DBManager(QWidget *parent)
	: QWidget{parent}, QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))
{
	setDatabaseName(QDir::currentPath() + "/Data.db");

    // Print error if database does not open
	if (!open()) {
		qDebug() << "Connection to database failed";
	} else {
        qDebug() << "Connection to database succeeded";
	}
}

DBManager::~DBManager()
{
    // Output when database closes
	if (open()) {
		qDebug() << "Connection to database has been closed";
		QSqlDatabase::close();
	}
}

DBManager* DBManager::instance()
{
    // Create one and only one instance of the database
	static DBManager instance;
	return &instance;
}

void DBManager::AddFood(const QString &city, const QString &food,
						const QString &price)
{
    // Finds and stores the id associated with the city name
	query.prepare("SELECT id FROM cities WHERE cityNames = :city");
	query.bindValue(":city", city);
	if (!query.exec()) {
		qDebug() << "DBManager::AddFood() : query failed";
		return;
	}
	query.first();
	int id = query.value(0).toInt();

    // Using the obtained id, a new food item and price is INSERTED
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

            // If query does not execute, print error
			if (!query.exec())
				qDebug() << "DBManager::ImportCities() : error executing query";

			// update progress bar
			progress.setValue(++count);
		}
		query.finish();
	}
}

void DBManager::UpdateFoodPrice(const QString &foodName, const QString &price)
{
    // Prep query
	query.prepare("UPDATE food SET price = :price WHERE food.foodNames = :foodName");

    // Bind values safely
	query.bindValue(":price", price);
	query.bindValue(":foodName", foodName);

    // If query does not execute, print error
	if (!query.exec())
		qDebug() << "DBManager::UpdateFoodPrice() : query failed";
	query.finish();
}

void DBManager::DeleteFood(const QString &foodName)
{
    // Prep query
	query.prepare("DELETE FROM food WHERE food.foodNames = :foodName");

    // Bind values safely
	query.bindValue(":foodName", foodName);

    // If query does not execute, print error
	if (!query.exec())
		qDebug() << "DBManager::DeleteFood() : query failed";
	query.finish();

}

void DBManager::CityToFoodNames(const QString &city, QStringList &foods)
{
    // Prep query
	query.prepare("SELECT foodNames FROM food, cities WHERE cities.cityNames = "
				  ":city AND cities.id = food.id");

    // Bind value safely
	query.bindValue(":city", city);

    // If query executes, return foods from given city
	if (query.exec()) {
		while (query.next())
			foods.push_back(query.value(0).toString());
		query.finish();
    } else { // If query does not execute, print error
		qDebug() << "DBManager::CityToFoodNames() : query failed";
	}
}

// Get price of specific food item
QString DBManager::FoodNameToPrice(const QString &food)
{
    // Prep query
	query.prepare("SELECT price FROM food WHERE food.foodNames = :food");

    // Bind value safely
	query.bindValue(":food", food);

    // If query executes, return price
	if (query.exec()) {
		query.first();
		return query.value(0).toString();
    } else { // If query does not execute, print error
		qDebug() << "DBManager::FoodNameToPrice() : query failed";
	}
	return QString("Error");
}

// Populate list of cities in database
void DBManager::GetCities(QStringList &cities)
{
    // Prep query
	query.prepare("SELECT cityNames FROM cities");

    // If query executes, populate object list
    if (query.exec()) {
		while (query.next())
			cities.push_back(query.value(0).toString());
		query.finish();
    } else { // If query does not execute, print error
		qDebug() << "DBManager::GetCities() : query failed";
	}
}

// Return distances between two cities
int DBManager::GetDistances(const QString &city1, const QString &city2)
{
    // Prep query
	query.prepare("SELECT distances FROM distance, cities WHERE "
				  "cities.cityNames = :city1 AND cities.id = distance.id AND "
				  "endCity = :city2");

    // Safely bind values
	query.bindValue(":city1", city1);
	query.bindValue(":city2", city2);

    // If query executes properly, return desired distance
	if (query.exec()) {
		query.first();
		return query.value(0).toInt();
    } else { // If query does not execute, print error
		qDebug() << "DBManager::GetDistances() : query failed";
	}

    // Can indicate that city name is wrong or not part of DB
	return -1;
}

// Create shopping list for use in purchase page
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
        else // If query fails, output error
        {
            qDebug() << "Query didn't execute properly";
        }
    }
}

// Get information used in cities table
void DBManager::GetCitiesTable(QStringList* cityNames, QVector<int>* distancesFromBerlin)
{
    // Prep query
	query.prepare("SELECT cities.citynames, distance.distances FROM cities, "
				  "distance WHERE distance.endcity = 'Berlin' AND cities.id = "
				  "distance.id;");

    // If query executes, load objects
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
    else // If query does not execute, print error
    {
        qDebug() << "GetCitiesTable query didn't execute properly";
    }
}

// Attempt login to administrator section
bool DBManager::LogIn(const QString &username, const QString &password)
{
    // Prep initial login bool
    bool found = false;

    // Prep query
    query.prepare("SELECT * FROM accounts WHERE username = :username AND password = :password AND level = 'ADMIN';");

    // Bind values safely
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    // If query executes successfully, check values
    if(query.exec())
    {
        // If values are correct, login
        if(query.next())
        {
            found = true;
            qDebug() << "Login Successfull";
        }
    }
    else // If query fails, print failure
    {
        qDebug() << "Login Query Failed";
    }

    return found;
}
