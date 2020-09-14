#include <QApplication>
#include "mainwindow.h"

#define Debug 1

#if Debug == 0

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}

#else

#include <QDebug>
#define print qDebug()

int main() {
	DBManager::instance();
	DBManager::instance()->addFood("Amsterdam", "pizza", "1000.20");
	return 0;
}

#endif
