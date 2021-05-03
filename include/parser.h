#ifndef PARSER_H
#define PARSER_H
#include "token.h"
#include "cfg.h"
#include "ll-table.h"

#include <stack>
#include <iostream>

class Node
{
public:
    string type;
    Node *parent;
    vector<Node> children;
    string value;

    Node(string type)
    {
        this->type = type;
    }
};

vector<int> getRow(string currentNode, Table llTable);
int getHeaderIndex(Table llTable, string tokenType);
Token tokenPeak(std::vector<Token> tokenStream);
Token tokenPop(std::vector<Token> tokenStream);
Node buildRawParseTree(CFG cfg, Table table, std::vector<Token> tokenStream);
#endif