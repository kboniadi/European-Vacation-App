#include <QApplication>
#include "mainwindow.h"

#define Debug 0

#if Debug == 0

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}

#else

#include "sortalgorithm.h"
#include "dbmanager.h"
#include <QDebug>

#define print qDebug()

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	DBManager::instance();

	// first city is always treated as the starting city!!!
	QStringList list = {"Berlin", "Amsterdam", "Brussels", "Budapest",
						"Hamburg", "Lisbon", "London", "Madrid", "Paris",
						"Prague", "Rome"};
	QStringList sortedList;

	// list is not modified, sortedList is
	algorithm::sort(list, sortedList);

	print << "Before sort:\n";
	print << list;
	print << "\nAfter sort:\n";
	print << sortedList;
	return 0;
}

#endif
