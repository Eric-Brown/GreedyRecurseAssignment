#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;
const int START_ARRAY_SZ = 2000;
const int END_ARRAY_SZ = 4000;
const int BAG_SIZE = 200;
struct item {
	double weight;
	double profit;
	bool operator > (item& b)
	{
		return ((profit / weight) > (b.profit / b.weight));
	}
	bool operator < (item& b)
	{
		return !((*this) > b);
	}
};
int global_shmobal = 0;
inline double fill() 
{
	return (rand() % 100) + 1;
}
int maxd(int a, int b)
{
	if (a<b) return b;
	else return a;
}

int gredRec(item items[], int itemIdx, int itemSize, int remainingWeight, std::unordered_map<int, int>& soFar)
{
	++global_shmobal;
	int realKey = itemIdx + (remainingWeight << 1);
	if (itemIdx == itemSize) return 0;
	if (soFar.find(realKey) != soFar.end()) return soFar[realKey];
	else if (items[itemIdx].weight <= remainingWeight)
	{
		int best = maxd(gredRec(items, itemIdx + 1, itemSize, remainingWeight, soFar), items[itemIdx].profit + gredRec(items, itemIdx + 1, itemSize, remainingWeight - items[itemIdx].weight, soFar));
		soFar[realKey] = best;
		return best;
	}
	else
	{
		int best = gredRec(items, itemIdx + 1, itemSize, remainingWeight, soFar);
		soFar[realKey] = best;
		return best;
	}
}

int greedyRecursive(item items[], int itemSize, int remainingWeight)
{
	using namespace std;
	unordered_map<int, int> checking;
	return gredRec(items, 0, itemSize, remainingWeight, checking);
}


template <class value>
int partition(value* toSort, int low, int high, int& count)
{
	//int size = (high - low) + 1;
	//int parititionIdx = low + size / 2;
	int parititionIdx = low;
	while (low != parititionIdx || high != parititionIdx)
	{
		while (low < parititionIdx)
		{
			++count;
			if (toSort[low] < toSort[parititionIdx])
			{
				std::swap(toSort[low], toSort[parititionIdx]);
				parititionIdx = low;
			}
			else ++low;
		}
		while (high > parititionIdx)
		{
			++count;
			if (toSort[high] > toSort[parititionIdx])
			{
				std::swap(toSort[high], toSort[parititionIdx]);
				parititionIdx = high;
			}
			else --high;
		}
	}
	return parititionIdx;
}
template <class value>
void quicksort(value* toSort, int low, int high, int& count)
{
	int size = (high - low) + 1;
	if (size <= 1) return;
	else if (size == 2)
	{
		++count;
		if (toSort[low] > toSort[high]) std::swap(toSort[low], toSort[high]);
	}
	else
	{
		int partitionIdx = partition(toSort, low, high, count);
		quicksort(toSort, low, partitionIdx - 1, count);
		quicksort(toSort, partitionIdx + 1, high, count);
	}
}
template <typename value>
void merge(value* lower, int lowSz, value* upper, int upSz)
{
	int lowIndex{}, upIndex{}, copyIndex{};
	value* destination = new value[lowSz + upSz];
	while (lowIndex != lowSz && upIndex != upSz)
	{
		++global_shmobal;
		if (lower[lowIndex] > upper[upIndex])
			destination[copyIndex++] = lower[lowIndex++];
		else destination[copyIndex++] = upper[upIndex++];
	}
	while (lowIndex != lowSz)
	{
		++global_shmobal;
		destination[copyIndex++] = lower[lowIndex++];
	}
	while (upIndex != upSz)
	{
		++global_shmobal;
		destination[copyIndex++] = upper[upIndex++];
	}
	for (size_t i = 0; i < lowSz + upSz; i++)
	{
		lower[i] = destination[i];
	}
	delete destination;

}
template <typename value>
void mergesort(value* toSort, int size)
{
	if (size <= 1) return;
	mergesort(toSort, size / 2);
	mergesort(toSort + size / 2, size - size / 2);
	merge(toSort, size / 2, toSort + size / 2, size - size / 2);
}
double getProfit(int arraySz, item items[])
{
	int remainingWeight = BAG_SIZE;
	int profit{};
	int i = 0;
	while (remainingWeight && i < arraySz)
	{
		++global_shmobal;
		if (remainingWeight - items[i].weight >= 0)
		{
			profit += items[i].profit;
			remainingWeight -= items[i].weight;
		}
		i++;
	}
	return profit;
}

void printVector(const std::vector<item>& toPrint)
{
	for (size_t i = 0; i < toPrint.size(); i++)
	{
		std::cout << toPrint.at(i).profit << " "
			<< toPrint.at(i).weight << " "
			<< toPrint.at(i).profit/toPrint.at(i).weight << "\n";
	}
	std::cout << std::endl;
}
void main()
{
	time_t currTime;
	time(&currTime);
	srand(currTime);

	std::vector<item> items{};

	double W = BAG_SIZE;
	double fraction = 0;
	int i = 0;
	double runningW = 0;
	double amount = 0;
	int iAmount = 0;
	for (int i = START_ARRAY_SZ; i <= END_ARRAY_SZ; i++)
	{
		global_shmobal = 0;

		for (int j = 0; j < i; j++)
			items.push_back({ fill(), fill() });
		mergesort(&items.front(), i);
		//printVector(items);

		//sort(&items.front(), &items.back(), [](item a, item b){++global_shmobal; return a.profit / a.weight > b.profit / b.weight; });
		//cout << "Input size: " << i << endl;
		//cout << "Dynamic Solution: " << getProfit(i, &items.front());
		int dynamicOpCount = global_shmobal;
		global_shmobal = 0;
		greedyRecursive(&items.front(), i, BAG_SIZE);

		//cout << "\tRecursive Solution: " << greedyRecursive(&items.front(), i, BAG_SIZE) << endl;
		//cout << "Op count for greedy: ";
		cout << global_shmobal << endl;
		//cout << "Op count for Dynamic: " << dynamicOpCount << endl;
		getchar();
	}
}
