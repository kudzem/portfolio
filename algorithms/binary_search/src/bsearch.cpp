#include "bsearch.h"

namespace kudzem_algorithms
{
	int bsearch(int* arr, size_t arr_size, int key) {

		size_t left = 0;
		size_t right = arr_size - 1;
		//0 9 4
		//4 9 6
		//6 9 8
		//8 9 8
		//8 9 8

		while (true) {
			size_t middle = (left + right) / 2;
			if (arr[middle] == key) {
				return middle;
			}
			else if (left + 1 == right) {
				if (arr[right] == key) {
					return right;
				}
			    break;
			}

			key < arr[middle] ? right = middle : left = middle;
		}
		return -1;
	}
}