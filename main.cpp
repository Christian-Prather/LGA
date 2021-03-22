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

using namespace std;

int main(int argc, char **argv)
{
    string inputFile = "../testFiles/biglanguage_grammar.cfg";

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

    //set<ItemSet> itemSets;
    ItemSet itSet;
    itSet.itemSet = vecItem;
    itSet.parentItemSetGrammarSymbol = cfg.startSymbol;
    itSet.parentItemSetIndex = 0;
    //itemSets.insert(itSet);

    //set<ItemSet>::iterator it = itemSets.begin();

    //while (it != itemSets.end()) {
    cout << "Original Item Set:\n";
    printItemSet(itSet);
    cout << "Item Set After Closure:\n";
    itSet = closure(itSet, cfg);
    printItemSet(itSet);
    vector<ItemSet> itemSets;
    itemSets.push_back(itSet);
    for (auto symbol : cfg.terminals)
    {
        ItemSet newSet;
        for (auto item : itSet.itemSet)
        {
            if (symbolRight(symbol, item))
            {
                Item newItem = goTo(item);
                newSet.itemSet.push_back(newItem);
            }
        }
        newSet = closure(newSet, cfg);
        itemSets.push_back(newSet);
    }

    for (auto symbol : cfg.nonTerminals)
    {
        ItemSet newSet;
        for (auto item : itSet.itemSet)
        {
            if (symbolRight(symbol, item))
            {
                Item newItem = goTo(item);
                newSet.itemSet.push_back(newItem);
            }
        }
        if (!newSet.itemSet.empty())
        {
            newSet = closure(newSet, cfg);
            itemSets.push_back(newSet);
        }
    buildTable(cfg);

    cout << "GOTO:///////////////////////////////" << endl;
    for (auto set : itemSets)
    {
        printItemSet(set);
    }

    //}
}