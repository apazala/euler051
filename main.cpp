#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <cstring>

using namespace std;

unordered_map<int, vector<int>*> clusters;
char GreaterDigitTable[128] = { -1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 };


int ipow(int x, int pow)
{
	if (pow == 0)
		return 1;

	for (int ret = 1; ; x *= x)
	{
		if ((pow & 1) == 1)
			ret *= x;

		pow >>= 1;
		if (pow == 0)
			return ret;

	}
}

void SaveValue(int digeq0, vector<char>& chardig, int p)
{
	vector<char> savedig(chardig);
	int digeq = digeq0;
	int v = 0;
	while (digeq != 0)
	{
		int d = GreaterDigitTable[digeq];
		digeq ^= (1 << d);
		savedig[d] = (char)0;
	}

	for (int i = 0; i < chardig.size(); i++)
		v = v * 10 + savedig[i];

	int tag = ((v << 7) + digeq0);

	vector<int>* list = new vector<int>(1, p);


	auto iter = clusters.insert(make_pair(tag, list));

	if (!iter.second) {
		delete list;
		iter.first->second->push_back(p);
	}
}

void Populate(char d, int istart, int digeq, int k, vector<char>& chardig, int p)
{
	if (k == 0)
	{
		SaveValue(digeq, chardig, p);
		return;
	}
	else if (istart < 0) return;

	k--;
	for (int i = istart; i >= k; i--)
	{
		if (chardig[i] == d)
		{
			Populate(d, i - 1, digeq | (1 << i), k, chardig, p);
		}
	}
}


void PrimesList(int upperBound, vector<int>& primesList);

void compute(int n, int k, int l) {
	int uplimit = ipow(10, n);
	int lowlimit = uplimit / 10;


	vector<int> primesList;
	PrimesList(uplimit, primesList);

	int i = static_cast<int>(upper_bound(primesList.begin(), primesList.end(), lowlimit) - primesList.begin());

	vector<char> chardig(n, '\0');
	int counts[10];
	while (i < primesList.size())
	{
		memset(counts, 0, 10 * sizeof(int));
		int p = primesList[i++];
		int p0 = p;
		int j = n - 1;
		int d;
		while (p > 0)
		{
			d = p % 10;
			p /= 10;
			counts[d]++;
			chardig[j--] = (char)d;
		}

		for (d = 0; d <= 9; d++)
		{
			if (counts[d] >= k)
			{
				Populate((char)d, n - 1, 0, k, chardig, p0);
			}
		}

	}

	vector<int> badsol;
	badsol.push_back(99999999);

	vector<int> *solution = &badsol;

	for (auto& it : clusters)
	{
		auto list = it.second;
		if (list->size() >= l)
		{
			i = 0;
			while (list->at(i) == solution->at(i))
				i++;

			if (list->at(i) < solution->at(i))
				solution = list;
		}
	}

	for (i = 0; i < l; i++)
		cout << solution->at(i) << ' ';
	cout << endl;

}

int main()
{
	int n = 6, k = 3, l = 8;
    
    compute(n, k, l);

	return 0;
}

void PrimesList(int upperBound, vector<int>& primesList)
{

	vector<bool> isPrimeArray(upperBound + 1, true);
	isPrimeArray[0] = isPrimeArray[1] = false;

	int sqr = sqrt(upperBound);
	for (int i = 0; i <= sqr; i++)
		if (isPrimeArray[i])
		{
			primesList.push_back(i);
			for (int j = i * i; j <= upperBound; j += i)
				isPrimeArray[j] = false;

		}

	for (int i = sqr + 1; i <= upperBound; i++)
		if (isPrimeArray[i])
			primesList.push_back(i);

}