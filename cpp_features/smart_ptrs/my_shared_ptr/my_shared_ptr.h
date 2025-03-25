#pragma once

template <class T>
class my_shared_ptr {

    T* _ptr;
    long* __shr_cntr;

public:
    my_shared_ptr(T* ptr) : _ptr(ptr), __shr_cntr(new long(1)){
        std::cout << "CONST def" << std::endl;
    }

    my_shared_ptr(my_shared_ptr& ptr) {
        std::cout << "CONST copy" << std::endl;
        _ptr = ptr._ptr;
        __shr_cntr = ptr.__shr_cntr;
        (*__shr_cntr)++;
    }

    my_shared_ptr(my_shared_ptr&& other) {
        std::cout << "CONST move" << std::endl;
        _ptr = other._ptr;
        other._ptr = nullptr;

        __shr_cntr = other.__shr_cntr;
        other.__shr_cntr = nullptr;
    }

    ~my_shared_ptr() {

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

    long use_count() const { return *__shr_cntr; }

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