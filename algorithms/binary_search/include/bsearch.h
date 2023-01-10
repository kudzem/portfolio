#pragma once

namespace kudzem_algorithms
{
	bool less(void* a, void* b, size_t size);
	bool greater(void* a, void* b, size_t size);

	size_t bsearch(void* arr, size_t arr_size, void* key, size_t key_size, bool (*cmp)(void*, void*, size_t) = less);
}