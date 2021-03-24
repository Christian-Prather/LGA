#include <iostream>
#include "include/item.h"

string progress(Item &item)
{
    string grammarSymbolTraversed;
    grammarSymbolTraversed = item.rule.RHS.at(item.progressMarkerIndex);

    item.progressMarkerIndex++;

    return grammarSymbolTraversed;
}

void printItemSet(ItemSet iSet)
{
    cout << "*** ITEM SET " << iSet.index << " ***\n";
    cout << "Parent Item Set Grammar Symbol: " << iSet.parentItemSetGrammarSymbol << endl;
    cout << "Rules:\n";
    for (Item i : iSet.itemSet)
    {
        cout << i.rule.LHS << " -> ";
        int ct = 0;
        for (string s : i.rule.RHS)
        {
            if (ct == i.progressMarkerIndex)
                cout << "* ";
            cout << s << " ";
            if ((ct == i.rule.RHS.size() - 1) && (i.rule.RHS.size() == i.progressMarkerIndex))
                cout << "* ";
            ct++;
        }
        cout << endl;
    }
    cout << "****************\n";
}