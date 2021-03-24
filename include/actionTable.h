#ifndef ACTION_TABLE_H
#define ACTION_TABLE_H

#include <vector>

#include "item.h"
#include "follow.h"
#include "goTo.h"

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

// Searches for shifts
int searchSets(vector<ItemSet> itemSets, ItemSet searchItemSet)
{
    int index;
    for (auto itemSet : itemSets)
    {
        bool matchSet = false;
        if (itemSet.itemSet.size() != searchItemSet.itemSet.size())
        {
            continue;
        }
        for (int i = 0; i < searchItemSet.itemSet.size(); i++)
        {
            auto searchItem = searchItemSet.itemSet[i];
            bool matchItem = false;

            for (Item item : itemSet.itemSet)
            {
                if ((sameRule(item.rule, searchItem.rule)) && (item.progressMarkerIndex == searchItem.progressMarkerIndex))
                {
                    matchItem = true;
                }
            }
            if (!matchItem)
            {
                break;
            }
            if (i == searchItemSet.itemSet.size() - 1)
            {
                return itemSet.index;
            }
        }
    }
    return index;
}

int grammarRule(vector<string> rhs, CFG cfg)
{
    for (int i = 0; i < cfg.rules.size(); i++)
    {
        auto rule = cfg.rules[i];
        if (rule.RHS == rhs)
        {
            return i;
        }
    }
    return -1;
}

ActionTable buildActionTable(vector<ItemSet> itemSets, CFG cfg)
{
    ActionTable actionTable;

    // Combine sets
    set<string> symbols(cfg.terminals);
    symbols.insert(cfg.nonTerminals.begin(), cfg.nonTerminals.end());

    for (ItemSet itemSet : itemSets)
    {
        // Initialize Row
        SlrRow row;
        for (int i = 0; i < symbols.size(); i++)
        {
            ActionGoTO entity;
            entity.action = None;
            entity.goTo = -1;
            row.entries.push_back(entity);
        }
        for (Item item : itemSet.itemSet)
        {
            if (item.progressMarkerIndex < item.rule.RHS.size())
            {
                string X = item.rule.RHS[item.progressMarkerIndex];
                int xIndex = 0;
                for (string symbol : symbols)
                {
                    if (symbol == X)
                    {
                        break;
                    }
                    xIndex++;
                }
                row.entries[xIndex].action = Shift;
                ItemSet gotoSet = goTo(itemSet, X, cfg);
                int gotoSetIndex = searchSets(itemSets, gotoSet);
                row.entries[xIndex].goTo = gotoSetIndex;
            }

            else if (item.progressMarkerIndex == item.rule.RHS.size())
            {
                int grammar = grammarRule(item.rule.RHS, cfg);
                if (grammar != -1)
                {
                    set<string> followT;
                    FollowResult follow = followSet(item.rule.LHS, followT, cfg);
                    set<string>::iterator terminalsIt = cfg.terminals.begin();
                    for (int i = 0; i < cfg.terminals.size(); i++)
                    {
                        for (string f : follow.F)
                        {
                            if (f == *terminalsIt)
                            {
                                row.entries[i].action = Reduce;
                                row.entries[i].goTo = grammar;
                            }
                        }
                        terminalsIt++;
                    }
                }
            }
        }
        actionTable.rows.push_back(row);
    }
    return actionTable;
}

#endif