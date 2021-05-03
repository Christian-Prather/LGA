#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <ctype.h>

#include "include/util.h"

bool
contains_upper(std::string str)
{
    for (const char& c : str) {
        if (isupper(c))
            return true;
    }

    return false;
}

bool
contains_lower(std::string str)
{
    for (const char& c : str) {
        if (islower(c))
            return true;
    }

    return false;
}

/**
 * trim() - remove the whitespace at the start and end of a string
 *
 * @s   The string to be trimmed.
 * 
 * Returns the string s without any whitespace at the ends.
 */
std::string
trim(const std::string& s)
{
    if (s.size() == 0)
        return s;

    size_t start = 0;
    size_t end = s.size() - 1;

    while (isspace(s[start]))
        ++start;
    while (isspace(s[end]))
        --end;

    return std::string(s.begin() + start, s.begin() + end + 1);
}

/**
 * split() - splits a string on whitespace
 *
 * @s   The string being split.
 *
 * Uses a stringstream to obtain multiple substrings, split by whitespace.
 * Returns this result as a vector.
 */
std::vector<std::string>
split(const std::string& s)
{
    if (s.size() == 0)
        return std::vector<std::string>();

    std::string trimmed = trim(s);
    std::istringstream iss(trimmed);

    std::vector<std::string> substrs;
    std::string substr;
    while (iss >> substr)
        substrs.push_back(substr);

    return substrs;
}

