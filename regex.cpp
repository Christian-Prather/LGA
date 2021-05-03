#include <set>
#include <vector>
#include <iostream>

#include "include/token.h"
#include "include/regex.h"

Token
scan_escaped(const std::string& regex_string, size_t index)
{
    if (index >= regex_string.size() - 1) {
        std::cerr << "scan_escaped(): Escape character \\ at end of string; "
            << "interpreting as literal \\." << std::endl;
        return Token("char", "\\");
    }

    // Record the list of escapable characters.
    std::set<char> esc { '|', '+', '(', ')', '-', 'n', '*', '.', 's', '\\' };

    // Match the escape sequence with the escapable characters.
    char esc_sequence = regex_string[index+1];
    if (esc.find(esc_sequence) == esc.end()) {
        std::cerr << "scan_escaped(): Unrecognized escape sequence; "
            << "interpreting " << esc_sequence
            << " as a literal." << std::endl;
        return Token("char", std::string(1, esc_sequence));
    } else {
        /* If the sequence is a space or newline escape, then return those
         * specific (alphabet-encoded) characters, otherwise return the escaped
         * character itself. */
        if (esc_sequence == 's')
            return Token("char", "x20");
        else if (esc_sequence == 'n')
            return Token("char", "x0a");
        else
            return Token("char", std::string(1, esc_sequence));
    }
}

Token
scan_normal(const std::string& regex_string, size_t index)
{
    // Extract the current character from the regex string
    char ch = regex_string[index];

    // Match that character, return the respective token
    if (ch == '|')
        return Token("pipe", "|");
    else if (ch == '+')
        return Token("plus", "+");
    else if (ch == '(')
        return Token("open", "(");
    else if (ch == ')')
        return Token("close", ")");
    else if (ch == '-')
        return Token("dash", "-");
    else if (ch == '*')
        return Token("kleene", "*");
    else if (ch == '.')
        return Token("dot", ".");
    else
        return Token("char", std::string(1, ch));
}

std::vector<Token>
scan_regex(const std::string& regex_string)
{
    std::vector<Token> tokens;
    size_t index = 0;
    while (index < regex_string.size()) {
        if (regex_string[index] == '\\') {
            tokens.push_back(scan_escaped(regex_string, index));
            index += 2;
        } else {
            tokens.push_back(scan_normal(regex_string, index));
            index += 1;
        }
    }

    tokens.push_back({"$", ""});
    return tokens;
}
