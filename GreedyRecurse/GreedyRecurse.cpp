// GreedyRecurse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <hash_map>
#include <algorithm>
//have a set of items
//each item has weight
//each item has profit
//it goes into napsack that has a maximum weight

struct item
{
	int weight;
	int profit;
};
void sortItems(item items[], int itemSize)
{
	using namespace std;
	sort(items, items + itemSize, [](item a, item b){return ((a.profit / a.weight) > (b.profit / b.weight));});
}
int greedyRecursive(item items[], int itemSize, int remainingWeight)
{
	using namespace std;
	hash_map<int, int> checking;
	return gredRec(items, 0, itemSize, remainingWeight, checking);
}

int gredRec(item items[], int itemIdx, int itemSize, int remainingWeight, std::hash_map<int, int>& soFar)
{
	struct hashKey
	{
		int currItem, currWeight;
	} theKey{ itemIdx, remainingWeight };
	std::hash<hashKey> hashfun;
	int realKey = hashfun(theKey);
	if (itemIdx == itemSize) return 0;
	if (soFar.find(realKey) != soFar.end()) return soFar[realKey];
	else if (items[itemIdx].weight < remainingWeight)
	{
		int best = std::max(gredRec(items, itemIdx + 1, itemSize, remainingWeight, soFar), items[itemIdx].profit + gredRec(items, itemIdx + 1, itemSize, remainingWeight - items[itemIdx].weight, soFar));
		soFar.insert(realKey, best);
	}
	else
	{
		int best = gredRec(items, itemIdx + 1, itemSize, remainingWeight, soFar);
		soFar.insert(realKey, best);
	}
}
int _tmain(int argc, _TCHAR* argv[])
{

	return 0;
}

