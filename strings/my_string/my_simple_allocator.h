#pragma once
#include <iostream>

template <class T>
class my_simple_allocator {
public:

    using value_type = T;

    T* allocate(size_t N) {
        std::cout << "Allocate " << N << std::endl;
        return reinterpret_cast<T*>(new char[N * sizeof(T)]);
    }

    void deallocate(T* ptr) {
        std::cout << "Deallocate" << std::endl;
        delete [] ptr;
    }

};
