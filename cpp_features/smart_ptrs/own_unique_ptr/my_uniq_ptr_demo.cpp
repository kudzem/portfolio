#include <iostream>
#include "my_unique_ptr.h"
#include <cassert>

struct A {
    int a;
    A(int val) : a(val) {}
};

int main()
{
    my_unique_ptr<int> a(new int(4));
    /*my_unique_ptr<int> b(a);
    a = b;*/

    my_unique_ptr<int> b(std::move(a));
    *b = 5;

    a = std::move(b);
    std::cout << *a << std::endl;

    if (b) {
        std::cout << "b unexpectedly not null" << std::endl;
    }

    auto aa = make_my_unique_ptr<A>(-3);
    std::cout << aa->a << std::endl;

    A* aptr = aa.release();
    delete aptr;

    return 0;
}