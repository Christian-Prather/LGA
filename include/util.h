#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>
#include <iostream>
#include <exception>


class ParseException : public std::exception {
private:
    std::string _msg;

public:
    ParseException(std::string msg) : _msg(msg) { }
    const char* what() const throw()
    {
        return "Failed to parse token stream. \
(Catch this exception for more info).";
    }
};

template <typename T>
void
print_separated(const std::vector<T>& strs, std::string separator)
{
    for (unsigned int i = 0; i < strs.size() - 1; ++i) {                        
        std::cout << strs[i] << separator;                                      
    }                                                                           
                                                                                
    std::cout << strs[strs.size() - 1];
}

template <typename T>
size_t
find_index(std::vector<T> arr, T elem)
{
    for (size_t i = 0; i < arr.size(); ++i)                                     
        if (arr[i] == elem)                                                     
            return i;                                                           
                                                                                
    // Return the vector's size if an element could not be found                
    return arr.size();
}

bool
contains_upper(std::string str);

bool
contains_lower(std::string str);

std::string
trim(const std::string& s);

std::vector<std::string>
split(const std::string& s);


#endif // UTIL_H
