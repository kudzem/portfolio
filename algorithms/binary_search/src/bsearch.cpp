#include "bsearch.h"

namespace kudzem_algorithms
{
	bool less(const int a, const int b) {
		return a < b;
	}

	bool greater(const int a, const int b) {
		return a > b;
	}

	int bsearch(int* arr, size_t arr_size, int key, bool (*cmp)(int, int)) {

		size_t left = 0;
		size_t right = arr_size - 1;

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

			cmp(key, arr[middle]) ? right = middle : left = middle;
		}
		return -1;
	}
}