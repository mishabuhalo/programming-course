// lab2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <functional>
#include <time.h>
using namespace std;



void swap(double* array, int i, int j)
{
	if (i == j) return;

	int tmp = array[j];
	array[j] = array[i];
	array[i] = tmp;
}

int lomuto_partition(double* array, int length)
{
	int pivot = array[0];
	int i = 1;
	int j = 1;

	for (; j < length; j++) {
		if (array[j] > pivot) {
			swap(array, i, j);
			i++;
		}
	}
	swap(array, 0, i - 1);
	return i - 1;
}

inline int find_pivot_median_of_three(double* array, int length)
{
	int first_pos = 0;
	int middle_pos = length % 2 ? length / 2 : (length / 2 - 1);
	int last_pos = length - 1;

	int first = array[first_pos];
	int middle = array[middle_pos];
	int last = array[last_pos];

	if (first <= middle) {
		if (middle <= last) {
			// first - middle - last
			return middle_pos;
		}
		else if (first <= last) {
			// first - last - middle
			return last_pos;
		}
		// last - first - middle
		return first_pos;
	}

	if (first <= last) {
		// middle - first - last
		return first_pos;
	}
	else if (middle <= last) {
		// middle - last - first
		return last_pos;
	}
	// last - middle - first
	return middle_pos;
}

void quick_sort(double* array, int length)
{
	if (length >1) {

		int pivot = find_pivot_median_of_three(array, length);

		swap(array, 0, pivot);

		int pos = lomuto_partition(array, length);

		quick_sort(array, pos);
		quick_sort(array + pos + 1, length - pos - 1);
	}
}

void selectionSort(double *array, int size)
{
	
	for (int i = 0; i < size; i++)
	{
		int tmp = array[0];
		for (int j = i + 1; j < size; j++)
		{
			if (array[i] < array[j])
			{
				tmp = array[j];
				array[j] = array[i];
				array[i] = tmp;
			}
		}
	}
}
int main()
{
	srand(time(NULL));
	cout << "Enter size of your array: ";
	int size;
	cin >> size;
	double *sorted_array = new double [size];

	for (int i = 0; i < size; i++)
	{
		sorted_array[i] = rand() % 100;
		cout << sorted_array[i] << "  ";
	}
	cout << endl;
	clock_t time = clock();

	//selectionSort(sorted_array, size);
	quick_sort(sorted_array, size);

	//sort(sorted_array, sorted_array +size, greater<int>());

	time = clock() - time;
	cout << "time is: " << (double)time/CLOCKS_PER_SEC << endl;

	for (int i = 0; i < size; i++)
	{
		cout << sorted_array[i] << "  ";
	}
	cout << endl;
	delete [] sorted_array;
	return 0;
}

