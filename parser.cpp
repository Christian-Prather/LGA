#include "include/parser.h"

int currentTokenIndex = 0;

vector<int> getRow(string currentNode, Table llTable)
{
    map<string, vector<int>>::iterator iter;
    for (iter = llTable.rows.begin(); iter != llTable.rows.end(); iter++)
    {
        if (iter->first == currentNode)
        {
            return iter->second;
        }
    }
}

int getHeaderIndex(Table llTable, string tokenType)
{
    for (int i = 0; i < llTable.headerRow.size(); i++)
    {
        if (llTable.headerRow[i] == tokenType)
        {
            return i;
        }
    }
}

Token tokenPeak(std::vector<Token> tokenStream)
{
    return tokenStream[currentTokenIndex];
}

Token tokenPop(std::vector<Token> tokenStream)
{
    auto nextToken = tokenStream[currentTokenIndex];
    currentTokenIndex++;
    return nextToken;
}

Node buildRawParseTree(CFG cfg, Table table, std::vector<Token> tokenStream)
{
    string MARKER = "MARKER";

    Node root("root");
    Node *currentNode = &root;

    stack<string> K;
    string startSymbol = cfg.startSymbol;
    K.push(startSymbol);

    while (K.size() > 0)
    {
        string x = K.top();
        K.pop();
        if (cfg.nonTerminals.find(x) != cfg.nonTerminals.end())
        {
            vector<int> tableRow = getRow(x, table);
            int columnInt = getHeaderIndex(table, tokenPeak(tokenStream).get_token_type());
            int ruleId = tableRow[columnInt] - 1;
            Rule rule = cfg.rules[ruleId];
            K.push(MARKER);
            auto R = rule.RHS;
            for (int i = R.size() - 1; i >= 0; i--)
            {
                K.push(R[i]);
            }
            Node newNode(x);
            newNode.parent = currentNode;
            currentNode->children.push_back(newNode);
            currentNode = &currentNode->children.back();
        }

        else if (cfg.terminals.find(x) != cfg.terminals.end() || x == "lambda" || x == "$")
        {
            if (cfg.terminals.find(x) != cfg.terminals.end() || x == "$")
            {
                if (x != tokenPeak(tokenStream).get_token_type())
                {
                    cout << "Invalid stream" << endl;
                    exit(-1);
                }
                x = tokenPop(tokenStream).get_token_type();
            }
            Node newNode(x);
            newNode.parent = currentNode;
            if (x != "lambda")
            {
                newNode.value = tokenStream[currentTokenIndex - 1].get_token_value();
            }
            else
            {
                newNode.value = "lambda";
            }

            currentNode->children.push_back(newNode);
        }
        else if (x == MARKER)
        {
            currentNode = currentNode->parent;
        }
    }
    currentTokenIndex = 0;
    return root;
}