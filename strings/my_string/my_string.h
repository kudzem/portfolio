#include <iostream>
#include <vector>
#include <memory>
#include "my_vector.h"

class my_string : public my_vector<char>
{
public:
    my_string(const char* origin_string) : my_vector(origin_string, strlen(origin_string)) {
    }

    my_string() : my_vector() {}

    size_t length() const {
        return size();
    }
};


std::ostream&
operator<<(std::ostream& os, const my_string& obj)
{
    const char* data = obj.get_data();
    if (data != nullptr) {

        size_t size = obj.size();

        while (size--) {
            os << *data;
            ++data;
        }
    }
    
    return os;
}