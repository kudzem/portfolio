#pragma once

namespace kudzem_algorithms
{
	bool less(int a, int b);
	bool greater(int a, int b);

	int bsearch(int* arr, size_t arr_size, int key, bool (*cmp)(int, int) = less);
}