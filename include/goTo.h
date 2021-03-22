#ifndef GOTO_H
#define GOTO_H

#include <vector>
#include <string>

#include "cfg.h"
#include "item.h"

using namespace std;

Item goTo(Item item)
{
    Item updatedItem;
    updatedItem.progressMarkerIndex = item.progressMarkerIndex;
    updatedItem.rule = item.rule;

    updatedItem.progressMarkerIndex++;
    return updatedItem;
}

bool symbolRight(string symbol, Item item)
{
    // for (int i = item.progressMarkerIndex; i < item.progressMarkerIndex + 2; i++)
    // {
        if (item.rule.RHS[item.progressMarkerIndex] == symbol)
        {
            return true;
        }
    // }
    return false;
}

#endif