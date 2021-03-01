#ifndef LIST_H_UNION
#define LIST_H_UNION

#include <vector>
#include <set>
#include <string>

using namespace std;

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

#endif