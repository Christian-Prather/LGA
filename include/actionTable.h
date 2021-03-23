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

                if (item.progressMarkerIndex == searchItem.progressMarkerIndex + 1 && item.rule.RHS[item.progressMarkerIndex] == character)
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

// vector<int> reduce(vector<ItemSet> ItemSets, Item )

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
    // Combine sets

    set<string> header(cfg.terminals);
    header.insert(cfg.nonTerminals.begin(), cfg.nonTerminals.end());

    for (auto itemSet : itemSets)
    {
        for (auto rule : itemSet.itemSet)
        {
            // S-> fa*
            // Intialixe Row
            SlrRow row;
            for (int i = 0; i < header.size(); i++)
            {
                ActionGoTO entity;
                entity.action = None;
                entity.goTo = -1;
                row.entries.push_back(entity);
            }

            vector<int> matches = searchSets(itemSets, rule, header);

            if (matches.size() > 0)
            {
                ActionGoTO entry;
                entry.action = Shift;
                entry.goTo = matches[0]; // Doesnt handle conflic

                // SlrRow row;
                row.entries.push_back(entry);
                actionTable.rows.push_back(row);
                continue;
            }

            if (rule.progressMarkerIndex == rule.rule.RHS.size() - 1)
            {
                int grammar = grammarRule(rule.rule.RHS, cfg);
                if (grammar != -1)
                {
                    set<string> followT;
                    FollowResult follow = followSet(rule.rule.LHS, followT, cfg);
                    set<string>::iterator terminalsIt = cfg.terminals.begin();
                    for (int i = 0; i < cfg.terminals.size(); i++)
                    {
                        for (string f : follow.F)
                        {
                            if (f == *terminalsIt)
                            {
                                row.entries[i].action = Reduce;
                                row.entries[i].goTo = grammar;
                                // row.[i] = entry;
                            }
                        }
                        terminalsIt++;
                    }
                    set<string>::iterator nonTerminalsIt = cfg.terminals.begin();

                    for (int i = 0; i < cfg.nonTerminals.size(); i++)
                    {
                        for (string f : follow.F)
                        {
                            if (f == *nonTerminalsIt)
                            {
                                row.entries[i].action = Reduce;
                                row.entries[i].goTo = grammar;
                            }
                        }
                        nonTerminalsIt++;
                    }
                }
            }
        }
    }
}

#endif