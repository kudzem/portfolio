#pragma once

template <class T>
class my_unique_ptr
{
    T* _ptr;
public:
    my_unique_ptr(T* ptr) : _ptr(ptr) {}
    my_unique_ptr(my_unique_ptr& other) = delete;
    my_unique_ptr(my_unique_ptr&& other) {
        _ptr = other._ptr;
        other._ptr = nullptr;
    }
    ~my_unique_ptr() { delete _ptr; }
    T& operator= (my_unique_ptr& other) = delete;
    my_unique_ptr<T>& operator= (my_unique_ptr&& other) {
        delete _ptr;
        _ptr = other._ptr;
        other._ptr = nullptr;
        return *this;
    };
    T& operator* () { return *_ptr; }
    T* operator-> () { return _ptr; }
    T* release() { T* tmp = nullptr; std::swap(tmp, _ptr); return tmp; }
    operator bool() const {
        return _ptr != nullptr;
    }

};

template <class T, typename... Args>
my_unique_ptr<T>
make_my_unique_ptr(Args... args) {
    T* obj = new T(args...);
    return my_unique_ptr<T>(obj);
}