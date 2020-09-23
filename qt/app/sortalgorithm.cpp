#include "sortalgorithm.h"

void algorithm::sort(const QStringList &list, QStringList &sortedList)
{
	sort(list, list.size(), sortedList);
}

#define distance(city1, city2) DBManager::instance()->GetDistances(city1, city2)
void algorithm::sort(QStringList list, int size, QStringList &sortList)
{
	// base case
	if (size == 0)
		return;

	if (sortList.size() == 0) {
		sortList.push_back(list.front());
		list.pop_front();
		size--;
		// sub base case
		if (size == 0) return;
	}

	QString temp = list.front();
	int dist = distance(sortList.last(), temp);

	for (int i = 0; i < size; i++) {
		if (distance(sortList.last(), list.at(i)) < dist) {
			dist = distance(sortList.last(), list.at(i));
			temp = list.at(i);
		} else if (size == 1) {
			temp = list.front();
			break;
		}
	}

	sortList.push_back(temp);
	list.removeAll(temp);
	return sort(list, size - 1, sortList);
}
#undef distance
