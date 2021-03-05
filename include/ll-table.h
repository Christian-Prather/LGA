#ifndef LL_TABLE_H
#define LL_TABLE_H

#include <vector>
#include <string>
#include <map>
#include "cfg.h"

using namespace std;

#define NA 0

struct Table
{
    vector<string> headerRow;
    map<string, vector<int>> rows;
};

Table buildTable(CFG cfg)
{
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
    return llTable;
}

#endif