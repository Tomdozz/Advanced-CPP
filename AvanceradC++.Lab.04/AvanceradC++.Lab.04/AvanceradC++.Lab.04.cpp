// AvanceradC++.Lab.04.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <list>
#include <numeric>
#include <random>
#include <iostream>
#include <forward_list>
#include <iterator>


using namespace std;

vector<int> v(100);
int arr[101];
forward_list<int> fList = { 20,5,15,40,50,30 };
forward_list<int>::iterator it;

void SortAsc();
void SortDec();
void RemoveIf();
template<class ForwardItterator>
void ForwardSort(ForwardItterator begin, ForwardItterator end);

template<typename InputIt1, typename InputIt2, typename OutputIt>
OutputIt my_merge(InputIt1 first1,
	InputIt1 end1,
	InputIt2 first2,
	InputIt2 end2,
	OutputIt out)
{
	while (first1 != end1) {
		if (first2 == end2)
			return std::copy(first1, end1, out);

		if (*first1 < *first2) {
			*out = *first1;
			++first1;
		}
		else {
			*out = *first2;
			++first2;
		}
		++out;
	}

	return std::copy(first2, end2, out);
}

template<typename InputIt>
void mergesort(InputIt first, InputIt end)
{
	size_t n = std::distance(first, end);
	if (n < 2)
		return;
	InputIt mid = first;

	for (size_t i = 0; i < n / 2; ++i)
		++mid;

	std::vector<typename InputIt::value_type> res;
	mergesort(first, mid);
	mergesort(mid, end);
	my_merge(first, mid, mid, end, std::back_inserter(res));
	std::copy(res.begin(), res.end(), first);
}

int main()
{
	//Initilize containers and randomize them
	for (size_t i = 0; i < 101; i++)
	{
		arr[i] = i;
	}
	/*for (size_t i = 100; i > 0; i--)
	{
		fList.push_front(i);
	}*/
	mergesort(fList.begin(), fList.end());
	//fList.sort();
	//it = fList.insert_after(it, fList.begin(), fList.end());

	iota(v.begin(), v.end(), 0);
	random_shuffle(v.begin(), v.end());
	random_shuffle(begin(arr), end(arr));
	//--------------------------------------------------------

	cout << "Array before sort:" << endl;
	for (size_t i = 0; i < 101; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	cout << "Vector before sort:" << endl;
	for (auto i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	//SortAsc();
	SortDec();
	RemoveIf();
	cout << "Array after sort:" << endl;
	for (size_t i = 0; i < 101; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	cout << "Vector after sort:" << endl;
	for (auto i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	//ForwardSort(fList.begin(), fList.end());
	cin.get();
	return 0;
}

void SortAsc()
{
	sort(v.begin(), v.end());
	sort(begin(arr), end(arr));
}
void SortDec()
{
	sort(begin(arr), end(arr), [](const int a, const int b) {return a > b; });
	sort(v.rbegin(), v.rend());
}
void RemoveIf()
{
	remove_if(v.begin(), v.end(), [](const int& value) {return (value % 2) == 1; });
}