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

using namespace std;

int main(int argc, char **argv)
{
    string inputFile = "./testFiles/eplusnum.cfg";

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
   for (Rule r : cfg.rules) {
       if (r.LHS == cfg.startSymbol) {
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
    printItemSet(closure(itSet, cfg));
   //}
}