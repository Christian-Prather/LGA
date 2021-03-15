#ifndef ITEM_SETS
#define ITEM_SETS

#include <vector>
#include <string>

#include "cfg.h"

using namespace std;

struct Item
{
    Rule rule;

    // The progressMarkerIndex is the index of the RHS
    // of the rule where the progress marker is.
    // For example, if it's 0, then the "progress marker"
    // is at the beginning of the RHS and is a fresh start.
    // Ex: S -> * A B $ (* is the progress marker)
    // If it's 1, then the "progress marker" sits "inbetween"
    // the RHS index's 0 and 1
    // Ex: S -> A * B $ (* is the progress marker)
    int progressMarkerIndex = 0;
};

/**
 * @brief Will progress the item passed in one grammar symbol.
 * Incrementing the progress marker index and returning the 
 * grammar symbol that was traversed.
 * 
 * @param item 
 * @return string The grammar symbol that was traversed
 */
string progress(Item &item);

#endif