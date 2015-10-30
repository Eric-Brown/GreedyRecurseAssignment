#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct item {
	double weight;
	double profit;
}items[10];

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
	int realKey = itemIdx + (remainingWeight < 1);
	if (itemIdx == itemSize) return 0;
	if (soFar.find(realKey) != soFar.end()) return soFar[realKey];
	else if (items[itemIdx].weight < remainingWeight)
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
	double W = 200;
	double amount = 0;
	int i = 0;

	while (runningW <= W)
	{
		if (items[i].weight + runningW <= W)
		{
			amount = amount + items[i].profit;
		}
		runningW = runningW + items[i].weight;

		i++;
	}
	return amount;

}

void main()
{
	double W = 200;
	double fraction = 0;
	int i = 0;
	double runningW = 0;
	double amount = 0;
	int iAmount = 0;


	while (i < 10)
	{
		items[i].weight = fill();
		items[i].profit = fill();
		i++;
	}

	sortItems(items, 10);

	i = 0;
	while (i < 10) {
		cout << i << " ";
		cout << items[i].weight;
		cout << " ";
		cout << items[i].profit;
		cout << '\n';
		i++;
	}

	amount = getProfit();


	cout << amount;
	cout << " ";

	iAmount = greedyRecursive(items, 10, 200);

	cout << iAmount;


	cin.get();

}
