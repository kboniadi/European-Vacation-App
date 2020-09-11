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

