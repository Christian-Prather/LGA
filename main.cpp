/**
 * @file main.cpp
 * @author Alexandra Ernst
 * @brief LGA 13
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>

#include "include/cfg.h"
#include "include/predict.h"
#include "include/ll-table.h"
#include "include/item.h"
#include "include/closure.h"
#include "include/goTo.h"
#include "include/ll-tabular-parsing.h"
#include "include/actionTable.h"

using namespace std;

int main(int argc, char **argv)
{
    string inputFile = "../testFiles/lecture_example.txt";

    CFG cfg = readCfg(inputFile);
    printOutput(cfg);

    stack<Rule> T;
    for (string nonTerm : cfg.nonTerminals)
    {
        cout << nonTerm << " : " << endl;

        bool dToL = derivesToLambda(nonTerm, T, cfg);
        string lambda = "false";
        if (dToL == true)
        {
            lambda = "true";
        }
        cout << "Derives to lambda: " << lambda << endl;

        vector<string> XB;
        XB.push_back(nonTerm);
        set<string> firstT;
        FirstResult first = firstSet(XB, firstT, cfg);
        cout << "First set: ";
        for (string f : first.F)
        {
            cout << f << " ";
        }
        cout << endl;

        set<string> followT;
        FollowResult follow = followSet(nonTerm, followT, cfg);
        cout << "Follow set: ";
        for (string f : follow.F)
        {
            cout << f << " ";
        }
        cout << endl
             << endl;
    }

    for (Rule rule : cfg.rules)
    {
        cout << rule.LHS << " -> ";
        for (string s : rule.RHS)
        {
            cout << s << " ";
        }
        cout << ": " << endl;

        set<string> predict = predictSet(rule, cfg);
        cout << "predict set: ";
        for (string s : predict)
        {
            cout << s << " ";
        }
        cout << endl;
        cout << "Rule #: " << rule.identity << endl;
        cout << endl;
    }

    Table llTable = buildTable(cfg);

    vector<Item> vecItem;
    for (Rule r : cfg.rules)
    {
        if (r.LHS == cfg.startSymbol)
        {
            Item t;
            t.rule = r;
            t.progressMarkerIndex = 0;
            vecItem.push_back(t);
        }
    }

    ItemSet itemSet;
    itemSet.itemSet = vecItem;
    itemSet.parentItemSetGrammarSymbol = cfg.startSymbol;
    itemSet.parentItemSetIndex = 0;

    cout << "Original Item Set:\n";
    printItemSet(itemSet);
    cout << "Item Set After Closure:\n";
    itemSet = closure(itemSet, cfg);
    itemSet.index = 0;
    printItemSet(itemSet);

    vector<ItemSet> itemSets;
    itemSets.push_back(itemSet);

    for (string symbol : cfg.terminals)
    {
        ItemSet newSet = goTo(itemSet, symbol, cfg);
        if (!newSet.itemSet.empty())
        {
            newSet.index = itemSets.size();
            itemSets.push_back(newSet);
        }
    }

    for (auto symbol : cfg.nonTerminals)
    {
        ItemSet newSet = goTo(itemSet, symbol, cfg);
        if (!newSet.itemSet.empty())
        {
            newSet.index = itemSets.size();
            itemSets.push_back(newSet);
        }
    }

    cout << "GOTO:///////////////////////////////" << endl;
    for (auto set : itemSets)
    {
        printItemSet(set);
    }

    auto actionTable = buildActionTable(itemSets, cfg);
}