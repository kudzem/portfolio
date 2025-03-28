#pragma once

#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

template <class T>
class DynamicArray {
private:
    T* _data;
    size_t _size;
    size_t _capacity;

    void release_memory() {
        delete[] _data;
        _data = nullptr;
    }

    void extend()
    {
        if (_size == 0) {
            resize(1);
        }
        else if (_size == 1) {
            resize(2);
        }
        else {
            resize(static_cast<size_t>(pow(2, int(log2(_size) + 1))));
        }
    }
public:
    DynamicArray() : _data(nullptr), _size(0), _capacity(0) {}

    DynamicArray(const T* data, size_t size, size_t capacity = 0) {
        if (capacity == 0 && size > 0) {
            _capacity = static_cast<size_t>(pow(2, int(log2(size) + 1)));
        }
        else {
            _capacity = capacity;
        }
        _data = new T[_capacity];
        _size = std::min(_capacity, size);
        memcpy(_data, data, _size * sizeof(T));
    }

    DynamicArray(const DynamicArray& other)
    {
        _capacity = other._capacity;
        _size = other._size;
        _data = new T[_capacity];
        memcpy(_data, other._data, _size * sizeof(T));
    }
    DynamicArray& operator=(const DynamicArray& other) {
        DynamicArray tmp(other);
        std::swap(tmp._data, _data);
        std::swap(tmp._size, _size);
        std::swap(tmp._capacity, _capacity);
        return *this;
    }


    DynamicArray(size_t size) : DynamicArray() {
        if (size > 0) {
            _capacity = static_cast<size_t>(pow(2, int(log2(size) + 1)));
            _data = new T[_capacity];
            _size = std::min(_capacity, size);
            std::memset(_data, 0, _size * sizeof(T));
        }
    }

    void resize(size_t new_capacity) {
        T* _new_data = new T[new_capacity];
        _capacity = new_capacity;
        _size = std::min(_capacity, _size);
        std::memcpy(_new_data, _data, _size * sizeof(T));
        std::swap(_data, _new_data);
        delete[] _new_data;
    }

    T& operator[] (size_t idx) {
        return _data[idx];
    }

    T& at(size_t idx) {
        if (idx >= _size) {
            throw std::out_of_range("Idx out of array range");
        }
        return _data[idx];
    }

    void push_back(T item) {
        if (_size == _capacity) {
            extend();
        }
        _data[_size++] = item;
    }

    void pop_back() {
        if (_size == 0) return;
        --_size;

        if (2 * _size <= _capacity) {
            resize(_size);
        }
    }

    void pop_front() {
        if (_size == 0) return;

        --_size;
        T* _new_data = new T[_size];
        std::memcpy(_new_data, _data + 1, _size * sizeof(T));
        std::swap(_data, _new_data);
        delete[] _new_data;

        if (2 * _size <= _capacity) {
            resize(_size);
        }
    }

    void clear() {
        release_memory();
        _size = 0;
        _capacity = 0;
    }

    size_t get_size() const {
        return _size;
    }

    size_t get_capacity() const {
        return _capacity;
    }

    std::string print() const
    {
        std::string res;
        for (int i = 0; i < _capacity; ++i) {
            res += ((i < _size) ? std::to_string(_data[i]) : "_") + " ";
        }
        return res;
    }

    virtual
        ~DynamicArray() {
        release_memory();
    }
};

template <class T>
std::ostream&
operator<<(std::ostream& os, const DynamicArray<T>& obj)
{
    os << "Array params:" << std::endl
        << "size=" << obj.get_size() << ", capacity=" << obj.get_capacity() << std::endl;

    if (obj.get_capacity()) {
        os << "Array content:" << std::endl
            << obj.print() << std::endl;
    }
    os << std::endl;
    return os;
}