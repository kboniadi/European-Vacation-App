#ifndef SORTALGORITHM_H
#define SORTALGORITHM_H

#include <QStringList>
#include "dbmanager.h"

/*!
 * @brief The algorithm struct holds the sorting algorithm
 */
struct algorithm {
	/*!
	 * @brief sort driver function
	 * @param list; an unsorted list of cities
	 * @param sortedList; get updated with sorted list of cities
	 */
	static void sort(const QStringList &list, QStringList &sortedList);
private:
	/*!
	 * @brief sort recursive helper function
	 * @param list; an unsorted list of cities
	 * @param size;
	 * @param sortedList; get updated with sorted list of cities
	 */
	static void sort(QStringList list, int size,  QStringList &sortedList);
};

#endif // SORTALGORITHM_H
