#pragma once

template <class T>
class my_shared_ptr {

    T* _ptr = nullptr;
    long* __shr_cntr = nullptr;

public:

    my_shared_ptr() = default;

    my_shared_ptr(T* ptr) : _ptr(ptr), __shr_cntr(new long(1)){
        std::cout << "CONST prm" << std::endl;
    }

    my_shared_ptr(my_shared_ptr& other) : _ptr(other._ptr), __shr_cntr(other.__shr_cntr) {
        std::cout << "CONST copy" << std::endl;

        if (__shr_cntr) {
            (*__shr_cntr)++;
        }
    }

    my_shared_ptr(my_shared_ptr&& other) {
        std::cout << "CONST move" << std::endl;
        std::swap(_ptr, other._ptr);
        std::swap(__shr_cntr, other.__shr_cntr);
    }

    my_shared_ptr& operator=(my_shared_ptr& other) {
        std::cout << "ASSIGN copy" << std::endl;

        _ptr = other._ptr;
        __shr_cntr = other.__shr_cntr;

        if (__shr_cntr) {
            (*__shr_cntr)++;
        }

        return *this;
    }

    my_shared_ptr& operator=(my_shared_ptr&& other) {
        std::cout << "ASSIGN move" << std::endl;

        std::swap(_ptr, other._ptr);
        std::swap(__shr_cntr, other.__shr_cntr);

        return *this;
    }

    virtual ~my_shared_ptr() {

        if (__shr_cntr) {
            --(*__shr_cntr);

            if (*__shr_cntr == 0) {
                delete __shr_cntr;
                delete _ptr;
            }
        }
    }

    T& operator* () { return *_ptr; }
    T* operator-> () { return _ptr; }

    long use_count() const { return __shr_cntr ? *__shr_cntr : 0; }

    operator bool() const {
        return _ptr != nullptr;
    }

};

template <class T, typename... Args>
my_shared_ptr<T>
make_my_shared_ptr(Args... args) {
    T* obj = new T(args...);
    return my_shared_ptr<T>(obj);
}