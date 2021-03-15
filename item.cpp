#include "include/item.h"

string progress(Item &item)
{
    string grammarSymbolTraversed;
    grammarSymbolTraversed = item.rule.RHS.at(item.progressMarkerIndex);

    item.progressMarkerIndex++;

    return grammarSymbolTraversed;
}