#include "bsearch.h"
#include <cstring>

namespace kudzem_algorithms
{
	bool less(void* a, void* b, size_t size) {
		if (memcmp(a, b, size) < 0) return true;
		return false;
	}

	bool greater(void* a, void* b, size_t size) {
		if (memcmp(a, b, size) > 0) return true;
		return false;
	}

	size_t bsearch(void* arr, size_t arr_size, void* key, size_t key_size, bool (*cmp)(void*, void*, size_t)) {

		size_t left = 0;
		size_t right = arr_size - 1;

		while (true) {
			size_t middle = (left + right) / 2;
			if (memcmp((char*)arr + middle*key_size, key, key_size)==0) {
				return middle;
			}
			else if (left + 1 == right) {
				if (memcmp((char*)arr + right * key_size, key, key_size) == 0) {
					return right;
				}
			    break;
			}

			cmp(key, (char*)arr + middle* key_size, key_size) ? right = middle : left = middle;
		}
		return -1;
	}
}