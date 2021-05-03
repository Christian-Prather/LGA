#include "include/setUnion.h"
set<string> setUnion(set<string> first, set<string> second)
{
    set<string> result = first;
    for (auto x : second)
    {
        if (!result.count(x))
        {
            result.insert(x);
        }
    }
    return result;
}