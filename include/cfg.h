#ifndef LIST_H_CFG
#define LIST_H_CFG

#include <vector>
#include <string>
#include <set>

using namespace std;

struct Rule
{
    string LHS;
    vector<string> RHS;
    int identity;
};

struct CFG
{
    vector<Rule> rules;
    set<string> terminals;
    set<string> nonTerminals;
    string startSymbol;
};

CFG readCfg(string path);
void printOutput(CFG cfg);

#endif