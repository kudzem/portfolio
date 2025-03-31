#include <iostream>

template <class T>
class A {
    T value = 0;
    T another_value = 13;
public:
    T get_value() const {
        return value;
    }

    T get_another_value() {
        return value;
    }

    A(T value) : value(value) {
        std::cout << "Prm const A" << std::endl;
        print();
        ++counter;
    }

    A() = delete;

    A(const A&) = default;

    virtual void print() const {
        std::cout << ", class A" << std::endl;
    }

    virtual ~A() {
        std::cout << "Destr A" << std::endl;
        print();
        --counter;
        //std::runtime_error("Error in A destr");
        //throw std::runtime_error("Error in A destr");
    }

    static size_t counter;
};

size_t A<int>::counter = 0;
size_t A<long>::counter = 0;

template <class T>
class B : public A<T> {
public:
    void print() const override {
        std::cout << ", class B" << std::endl;
        throw std::runtime_error("Exception in A::print()");
    }

    virtual T get_value() const final {
        return A::get_value() * 10;
    }

    T get_another_value() const {
        return A::get_value() * 10;
    }

    B(T value) : A(value) {
        std::cout << "Prm const B" << std::endl;
        print();
    }

    ~B() {
        std::cout << "Destr B" << std::endl;
        print();
    }
};


class C : public A<long> {
public:
    void print() const {
        std::cout << ", class C" << std::endl;
    }


    C() : A(0) {
        std::cout << "Prm const C" << std::endl;
        print();
    }

    ~C() {
        std::cout << "Destr C" << std::endl;
        print();
        //std::runtime_error("Error in Ñ destr");
    }
};

void riskyFunction() {
    throw std::runtime_error("Something went wrong!");
}


int main() {

    try {
        riskyFunction();
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Handle an exception: " << e.what() << std::endl;
        //exit(0);
    }

    //exit(0);

    try
    {
        A<int>* a = new B<int>(3);
        a->print();
        std::cout << "Value = " << a->get_value() << std::endl;
        std::cout << "Another Value = " << ((B<int>*)a)->get_another_value() << std::endl;
        delete a;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Handle an exception: " << e.what() << std::endl;
        //exit(0);
    }


    try
    {
        C c;
        c.print();
        std::cout << "Value = " << c.get_value() << std::endl;
        std::cout << "Another Value = " << c.get_another_value() << std::endl;
        std::cout << "A<long>.counter = " << A<long>::counter << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Handle an exception: " << e.what() << std::endl;
        //exit(0);
    }
}