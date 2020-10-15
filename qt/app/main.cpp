#include <QApplication>
#include "mainwindow.h"
#include "usermanager.h"
#include <QtSql>

#define Debug 0

#if Debug == 0

int main(int argc, char *argv[])
{
/*
    QSqlDatabase userdb;
    userdb = QSqlDatabase::addDatabase("QSQLITE");
    userdb.setDatabaseName("user.db");

    if(!userdb.open())
    {
        qDebug() << "Error opening user database";
    }*/

	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}

#else

#include <QDebug>
#define print qDebug()

int main() {

	return 0;
}

#endif
