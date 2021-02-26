#ifndef CFG_H
#define CFG_H

#include <string>
#include <vector>
#include <set>
using namespace std;

struct CFGRule {
    string nonTerminal;
    vector<vector<string>> productions;
};

struct CFG {
    set<string> terminals;
    set<string> nonTerminals;
    vector<CFGRule> grammarRules;
    string startSymbol;
};

bool IsStrLowercase(string s);
CFG ReadFile(string file);
void PrintCFG(CFG cfg);

#endif