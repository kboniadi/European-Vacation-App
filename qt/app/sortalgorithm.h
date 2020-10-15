#ifndef SORTALGORITHM_H
#define SORTALGORITHM_H

#include <QStringList>
#include "dbmanager.h"

/*!
 * @brief The algorithm struct holds the sorting algorithm used for determining
 * minimum distance between cities
 */
struct algorithm {
	/*!
     * @brief Driver function
     * @param list; An unsorted list of cities
     * @param sortedList; Get updated with sorted list of cities
	 */
	static void sort(const QStringList &list, QStringList &sortedList);
private:
	/*!
     * @brief Recursive helper function
     * @param list; An unsorted list of cities
     * @param size; Size of list
     * @param sortedList; Updated sorted list of cities
	 */
	static void sort(QStringList list, int size,  QStringList &sortedList);
};

#endif // SORTALGORITHM_H
