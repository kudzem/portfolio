#include <iostream>
#include <map>

int fibonacci_naive(int n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;
	return fibonacci_naive(n - 1) + fibonacci_naive(n - 2);
}

std::map<int, int> M = { {0,0},{1,1} };
int fibonacci_with_memory(int n)
{
	auto v = M.find(n);
	if (v != M.end()) {
		return v->second;
	}

	int value = fibonacci_with_memory(n - 1) + fibonacci_with_memory(n - 2);
	M[n] = value;
	return value;
}

int fibonacci_dynamic(int n) {
	int a = 0;
	int b = 1;
	for (int i = 0; i < n; ++i) {
		int old_a = a;
		a = b;
		b = old_a + b;
	}

	return a;
}


int main()
{
	std::cout << "Fib(12) = " << fibonacci_naive(12) << std::endl;
	std::cout << "Fib(12) = " << fibonacci_with_memory(12) << std::endl;
	std::cout << "Fib(12) = " << fibonacci_dynamic(12) << std::endl;
	return 0;
}