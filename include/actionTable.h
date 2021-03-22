#ifndef ACTION_TABLE_H
#define ACTION_TABLE_H

#include <vector>
#include "item.h"
using namespace std;

enum Action
{
    Shift,
    Reduce
};

struct ActionGoTO
{
    Action action;
    int goTo;
};

struct SlrRow
{
    vector<ActionGoTO> entries;
};

struct ActionTable
{
    vector<SlrRow> rows;
};

bool sameRule(Rule one, Rule two)
{
    if (one.identity == two.identity && one.LHS == two.LHS && one.RHS == two.RHS)
    {
        return true;
    }
    return false;
}

ActionTable actionTable;

vector<int> searchSets(vector<ItemSet> itemSets, Item searchItem)
{
    vector<int> matches;
    for (auto set : itemSets)
    {
        for (auto item : set.itemSet)
        {
            if (item.progressMarkerIndex == searchItem.progressMarkerIndex + 1)
            {
                // Potential
                if (sameRule(item.rule, searchItem.rule))
                {
                    // Match
                    matches.push_back(set.index);
                }
            }
        }
    }
    return matches;
}

ActionTable buildActionTable(vector<ItemSet> itemSets)
{
    for (auto set : itemSets)
    {
        for (auto rule : set.itemSet)
        {
            // S-> fa*
            vector<int> matches = searchSets(itemSets, rule);
            {
                if (matches.size() > 0)
                {
                    ActionGoTO entry;
                    entry.action = Shift;
                    entry.goTo = matches[0]; // Doesnt handle conflic

                    SlrRow row;
                    row.entries.push_back(entry);
                    actionTable.rows.push_back(row);
                }
            }
        }
    }
}

#endif