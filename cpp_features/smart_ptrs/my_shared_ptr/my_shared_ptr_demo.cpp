#include <iostream>
#include "my_shared_ptr.h"
#include <cassert>

struct A {
    int a, b;
};

int main()
{
    int val = 123;
    my_shared_ptr<int> sp1(new int(val));

    assert(sp1 && "Error: pointer not initialized");
    assert(*sp1 == val && "Error: unexpected value inside of pointer");
    assert(sp1.use_count() == 1 && "Error: use count not equal to 1");


    my_shared_ptr<int> sp2(sp1);

    assert(sp1 && "Error: pointer not initialized");
    assert(*sp1 == val && "Error: unexpected value inside of pointer");
    assert(sp1.use_count() == 2 && "Error: use count not equal to 2");

    assert(sp1 && "Error: pointer not initialized");
    assert(*sp1 == val && "Error: unexpected value inside of pointer");
    assert(sp1.use_count() == 2 && "Error: use count not equal to 2");

    my_shared_ptr<int> sp3 = sp1;

    assert(sp1 && "Error: pointer not initialized");
    assert(*sp1 == val && "Error: unexpected value inside of pointer");
    assert(sp1.use_count() == 3 && "Error: use count not equal to 3");

    assert(sp3 && "Error: pointer not initialized");
    assert(*sp3 == val && "Error: unexpected value inside of pointer");
    assert(sp3.use_count() == 3 && "Error: use count not equal to 3");

    my_shared_ptr<int> sp4(std::move(sp2));

    assert(!sp2 && "Error: pointer should be null");

    assert(sp4 && "Error: pointer not initialized");
    assert(*sp4 == val && "Error: unexpected value inside of pointer");
    assert(sp4.use_count() == 3 && "Error: use count not equal to 3");

    my_shared_ptr<int> sp5;
    sp5 = std::move(sp4);
    sp4 = std::move(sp5);
    sp5 = std::move(sp4);

    assert(!sp4 && "Error: pointer should be null");

    assert(sp5 && "Error: pointer not initialized");
    assert(*sp5 == val && "Error: unexpected value inside of pointer");
    assert(sp5.use_count() == 3 && "Error: use count not equal to 3");

    auto sp10 = make_my_shared_ptr<A>();
    sp10->a = 13;

    my_shared_ptr<A> sp11(std::move(sp10));
    assert(sp11.use_count() == 1 && "Error: use count not equal to 0");
    my_shared_ptr<A> sp12 = sp11;
    assert(sp12.use_count() == 2 && "Error: use count not equal to 0");

    my_shared_ptr<A> empty_ptr;
    empty_ptr.use_count();
    assert(empty_ptr.use_count() == 0 && "Error: use count not equal to 0");

    my_shared_ptr<A> empty_ptr2(empty_ptr);
    empty_ptr2.use_count();
    assert(empty_ptr2.use_count() == 0 && "Error: use count not equal to 0");

    my_shared_ptr<A> empty_ptr3(empty_ptr);
    empty_ptr3.use_count();
    assert(empty_ptr3.use_count() == 0 && "Error: use count not equal to 0");

    std::cout << "Assign" << std::endl;
    my_shared_ptr<A> empty_ptr4;
    empty_ptr4 = empty_ptr3;
    empty_ptr3.use_count();
    assert(empty_ptr3.use_count() == 0 && "Error: use count not equal to 0");

    std::cout << "Assign" << std::endl;
    my_shared_ptr<A> empty_ptr5;
    empty_ptr5 = std::move(empty_ptr4);
    empty_ptr4.use_count();
    assert(empty_ptr5.use_count() == 0 && "Error: use count not equal to 0");

    return 0;
}