#ifndef SORTALGORITHM_H
#define SORTALGORITHM_H

#include <QStringList>
#include "dbmanager.h"

struct algorithm {
	static void sort(const QStringList &list, QStringList &sortedList);
private:
	static void sort(QStringList list, int size,  QStringList &sortedList);
};

#endif // SORTALGORITHM_H
