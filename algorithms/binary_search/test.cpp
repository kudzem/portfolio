#include <cassert>
#include <iostream>

#include "bsearch.h"

int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	assert(kudzem_algorithms::bsearch(arr, sizeof(arr) / sizeof(arr[0]), 11) == -1);
	assert(kudzem_algorithms::bsearch(arr, sizeof(arr) / sizeof(arr[0]), 10) == 9);
	assert(kudzem_algorithms::bsearch(arr, sizeof(arr) / sizeof(arr[0]), 5) == 4);
	assert(kudzem_algorithms::bsearch(arr, sizeof(arr) / sizeof(arr[0]), 1) == 0);

	int arr2[] = { -1, 9, -3, 8, 10, -6, -7, -4, -2, -5 };

	assert(kudzem_algorithms::bsearch(arr2, sizeof(arr) / sizeof(arr[0]), 11) == -1);

	int arr3[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

	//assert(kudzem_algorithms::bsearch(arr, sizeof(arr) / sizeof(arr[0]), 11) == -1);
	//assert(kudzem_algorithms::bsearch(arr, sizeof(arr) / sizeof(arr[0]), 10) == 9);
	//assert(kudzem_algorithms::bsearch(arr, sizeof(arr) / sizeof(arr[0]), 5) == 4);
	//assert(kudzem_algorithms::bsearch(arr, sizeof(arr) / sizeof(arr[0]), 1) == 0);

	std::cout << kudzem_algorithms::bsearch(arr3, sizeof(arr3)/sizeof(arr3[0]), 1) << std::endl;
	return 0;
}