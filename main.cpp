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
#include "include/derivesToLambda.h"
#include "include/first.h"
#include "include/follow.h"
#include "include/predict.h"
#include "include/llTable.h"

using namespace std;

int main(int argc, char **argv)
{
    string inputFile = "../testFiles/lectureExample.cfg";

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

    string lastNonTerm = "";
    vector<Rule> matchingRules;
    Table llTable;
    for (auto setIt = cfg.terminals.begin(); setIt != cfg.terminals.end(); setIt++)
    {
        llTable.headerRow.push_back(*setIt);
    }
    llTable.headerRow.push_back("$");

    for (auto rule : cfg.rules)
    {
        // Reference to new row, or existing row
        vector<int> &row = llTable.rows[rule.LHS];
        set<string> predict = predictSet(rule, cfg);
        for (int i = 0; i < llTable.headerRow.size(); i++)
        {
            string terminal = llTable.headerRow[i];
            // This terminal is in the predict set so mark the table
            // with the rule
            if (predict.count(terminal) > 0)
            {
                // See if terminal looked at befor
                if (row.size() <= i)
                {
                    row.push_back(rule.identity);
                }
                else
                {
                    row[i] = rule.identity;
                }
            }
            else
            {
                // Not there check if there is already an enrty in cell
                if (row.size() <= i)
                {
                    row.push_back(NA);
                }
            }
        }
    }

    cout << "LL TABLE" << endl;
    cout << "  ";
    for (auto terminal : llTable.headerRow)
    {
        cout << terminal << " ";
    }
    cout << endl;
    map<string, vector<int>>::iterator iter;
    for (iter = llTable.rows.begin(); iter != llTable.rows.end(); iter++)
    {
        cout << iter->first << " ";
        for (auto entry : iter->second)
        {
            cout << entry << " ";
        }
        cout << endl;
    }
}