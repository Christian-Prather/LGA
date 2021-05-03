#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>

class Token {
private:
    std::string _token_type;
    std::string _token_value;

public:
    Token();
    Token(std::string token_type);
    Token(std::string token_type, std::string token_value);

    std::string
    get_token_type() const noexcept;

    std::string
    get_token_value() const noexcept;
};

std::vector<Token>
read_token_stream(std::string file_path);

void
print_token_stream(const std::vector<Token>& tokens);

#endif // TOKEN_H
