#include <string>
#include <vector>
#include <fstream>

#include "include/util.h"
#include "include/token.h"

Token::Token() : _token_type(), _token_value() { }
Token::Token(std::string token_type) : _token_type(token_type) { }
Token::Token(std::string token_type, std::string token_value)
    : _token_type(token_type), _token_value(token_value) { }

std::string
Token::get_token_type() const noexcept
{
    return _token_type;
}

std::string
Token::get_token_value() const noexcept
{
    return _token_value;
}

/**
 * read_token_stream() - read a stream of tokens from a file
 *
 * @file_path   The file to read tokens from.
 *
 * Goes through a file with token definitions on each line, and returns a list
 * of those tokens as a vector.
 *
 * Token definitions can look like the following:
 *
 * TOKENTYPE [srcValue]
 *
 * Where a TOKENTYPE is mandatory, and a srcValue may be optionally included
 * with that token type. If more than two strings are provided per line, only
 * the first two are used. If there are no strings on a line, the line is
 * ignored.
 */
std::vector<Token>
read_token_stream(std::string file_path)
{
    std::vector<Token> tokens;
    std::ifstream token_file(file_path);
    std::string line;

    // For every line in the token file...
    while (std::getline(token_file, line)) {
        std::vector<std::string> token_items = split(line);
        
        // Check what to do with the token items found on that line.
        // Implicitly, ignore empty lines.
        if (token_items.size() == 1) {
            tokens.push_back(Token(token_items[0], "")); 
        } else if (token_items.size() == 2) {
            tokens.push_back(Token(token_items[0], token_items[1]));
        } else if (token_items.size() >= 3) {
            std::cerr << "read_token_stream(): Token has more than two "
                << "parameters. Only the first two will be used." << std::endl;
            tokens.push_back(Token(token_items[0], token_items[1]));
        }
    }

    // Push an end of input marker
    tokens.push_back({"$", ""});
    return tokens;
}

void
print_token_stream(const std::vector<Token>& tokens)
{
    std::cout << "--- TOKEN STREAM ---\n" << std::endl;
    for (const Token& token : tokens)
        std::cout << token.get_token_type() << " "
            << token.get_token_value() << std::endl;
    std::cout << "\n--- TOKEN STREAM ---" << std::endl;
}
