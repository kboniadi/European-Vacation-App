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

int main(int argc, char *argv[]) {
	return 0;
}

#endif
