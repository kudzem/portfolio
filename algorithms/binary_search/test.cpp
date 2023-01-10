#include <cassert>
#include <iostream>

#include "bsearch.h"

int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int key;

	key = 11; assert(kudzem_algorithms::bsearch(arr, sizeof(arr) / sizeof(arr[0]), &key) == -1);
	key = 10; assert(kudzem_algorithms::bsearch(arr, sizeof(arr) / sizeof(arr[0]), &key) == 9);
	key = 5; assert(kudzem_algorithms::bsearch(arr, sizeof(arr) / sizeof(arr[0]), &key) == 4);
	key = 1; assert(kudzem_algorithms::bsearch(arr, sizeof(arr) / sizeof(arr[0]), &key) == 0);

	int arr2[] = { -1, 9, -3, 8, 10, -6, -7, -4, -2, -5 };

	key = 11; assert(kudzem_algorithms::bsearch(arr2, sizeof(arr) / sizeof(arr[0]), &key) == -1);

	int arr3[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

	key = 11; assert(kudzem_algorithms::bsearch(arr3, sizeof(arr3) / sizeof(arr3[0]), &key, kudzem_algorithms::greater) == -1);
	key = 10; assert(kudzem_algorithms::bsearch(arr3, sizeof(arr3) / sizeof(arr3[0]), &key, kudzem_algorithms::greater) == 0);
	key = 5; assert(kudzem_algorithms::bsearch(arr3, sizeof(arr3) / sizeof(arr3[0]), &key, kudzem_algorithms::greater) == 5);
	key = 1; assert(kudzem_algorithms::bsearch(arr3, sizeof(arr3) / sizeof(arr3[0]), &key, kudzem_algorithms::greater) == 9);

	key = 1;
	std::cout << kudzem_algorithms::bsearch(arr3, sizeof(arr3)/sizeof(arr3[0]), &key, kudzem_algorithms::greater) << std::endl;
	return 0;
}