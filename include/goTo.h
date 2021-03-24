#ifndef GOTO_H
#define GOTO_H

#include <vector>
#include <string>

#include "cfg.h"
#include "item.h"
#include "closure.h"

using namespace std;

bool symbolRight(string symbol, Item item)
{
    if (item.rule.RHS[item.progressMarkerIndex] == symbol)
    {
        return true;
    }
    return false;
}

ItemSet goTo(ItemSet itemSet, string symbol, CFG grammar)
{
    ItemSet gotoSet;
    gotoSet.parentItemSetGrammarSymbol = symbol;

    for (Item item : itemSet.itemSet)
    {
        if (symbolRight(symbol, item))
        {
            Item newItem = item;
            progress(newItem);
            gotoSet.itemSet.push_back(newItem);
        }
    }
    gotoSet = closure(gotoSet, grammar);

    return gotoSet;
}

#endif