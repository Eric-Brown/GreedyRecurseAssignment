#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <time.h>
using namespace std;
const int ARRAY_SIZE = 30;
const int BAG_SIZE = 300;
struct item {
	double weight;
	double profit;
}items[ARRAY_SIZE];
int global_shmobal = 0;
double fill() {
	double randomNum;
	randomNum = (rand() % 100) + 1;

	return randomNum;

}
int maxd(int a, int b)
{
	if (a<b) return b;
	else return a;
}

int gredRec(item items[], int itemIdx, int itemSize, int remainingWeight, std::unordered_map<int, int>& soFar)
{
	global_shmobal++;
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



void sortItems(item items[], int itemSize) {
	sort(items, items + itemSize, [](item a, item b)
	{return ((a.profit / a.weight) >(b.profit / b.weight)); });
}

double getProfit()
{
	double runningW = 0;
	double W = BAG_SIZE;
	double amount = 0;
	int i = 0;

	while (runningW <= W && i < ARRAY_SIZE)
	{
		if (items[i].weight + runningW <= W)
		{
			amount += items[i].profit;
			runningW += items[i].weight;
		}

		i++;
	}
	return amount;

}

void main()
{
	time_t currTime;
	time(&currTime);
	srand(currTime);

	double W = BAG_SIZE;
	double fraction = 0;
	int i = 0;
	double runningW = 0;
	double amount = 0;
	int iAmount = 0;


	while (i < ARRAY_SIZE)
	{
		items[i].weight = fill();
		items[i].profit = fill();
		i++;
	}

	sortItems(items, ARRAY_SIZE);

	i = 0;
	while (i < ARRAY_SIZE) {
		cout << i << " ";
		cout << items[i].weight;
		cout << " ";
		cout << items[i].profit;
		cout << " " << items[i].profit / items[i].weight;
		cout << '\n';
		i++;
	}

	amount = getProfit();


	cout << amount;
	cout << " ";

	iAmount = greedyRecursive(items, ARRAY_SIZE, BAG_SIZE);

	cout << iAmount;


	cin.get();

}
