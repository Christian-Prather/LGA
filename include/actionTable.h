#ifndef ACTION_TABLE_H
#define ACTION_TABLE_H

#include <vector>
#include "item.h"
using namespace std;

enum Action
{
    Shift,
    Reduce,
    None
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

// Searches for shifts
vector<int> searchSets(vector<ItemSet> itemSets, Item searchItem, set<string> headerRow)
{
    vector<int> matches;

    for (auto set : itemSets)
    {
        for (auto item : set.itemSet)
        {
            for (auto character : headerRow)
            {

                if (item.progressMarkerIndex == searchItem.progressMarkerIndex + 1 && item.rule[item.progressMarkerIndex] == character)
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
    }
    return matches;
}

ActionTable buildActionTable(vector<ItemSet> itemSets, CFG cfg)
{
    // Combine sets

    set<string> header(cfg.terminals);
    header.insert(cfg.nonTerminals.begin(), cfg.nonTerminals.end());

    for (auto set : itemSets)
    {
        for (auto rule : set.itemSet)
        {
            // S-> fa*
            vector<int> matches = searchSets(itemSets, rule, header);
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
                else
                {
                    ActionGoTO entry;
                    entry.action = None;
                    entry.goTo = -1; // Doesnt handle conflic

                    SlrRow row;
                    row.entries.push_back(entry);
                    actionTable.rows.push_back(row);
                }
            }
        }
    }
}

#endif