#include "sortalgorithm.h"

void algorithm::sort(const QStringList &list, QStringList &sortedList)
{
	// helper recursive function
	sort(list, list.size(), sortedList);
}

#define distance(city1, city2) DBManager::instance()->GetDistances(city1, city2)
void algorithm::sort(QStringList list, int size, QStringList &sortList)
{
	// base case
	if (size == 0)
		return;

	// runs once and pushes the first cities from list to sortList
	// note: this city always represents the starting city in the list
	if (sortList.size() == 0) {
		sortList.push_back(list.front());
		list.pop_front();
		size--;
		// sub base case incase there is only one city in list
		if (size == 0) return;
	}

	QString temp = list.front();
	// always between most recently added city in sortList
	int dist = distance(sortList.last(), temp);

	// iterates through list and finds the shortest distance to last
	// city in the sortList
	for (int i = 0; i < size; i++) {
		int sudoDistance = distance(sortList.last(), list.at(i));
		if (sudoDistance < dist) {
			dist = sudoDistance;
			temp = list.at(i);
		} else if (size == 1) {
			temp = list.front();
			break;
		}
	}

	// addes the closest city to sortList and removes it from list
	sortList.push_back(temp);
	list.removeAll(temp);
	return sort(list, size - 1, sortList);
}
#undef distance
