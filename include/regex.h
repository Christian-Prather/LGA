#ifndef REGEX_H
#define REGEX_H

#include <vector>

#include "token.h"

Token
scan_escaped(const std::string& regex_string, size_t index);

Token
scan_normal(const std::string& regex_string, size_t index);

std::vector<Token>
scan_regex(const std::string& regex_string);

#endif // REGEX_H
