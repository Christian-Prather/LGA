#ifndef LIST_H_PREDICT
#define LIST_H_PREDICT

#include <set>
#include <string>

#include "follow.h"

using namespace std;

set<string> predictSet(Rule rule, CFG cfg)
{
    set<string> predict;

    set<string> firstT;
    FirstResult first = firstSet(rule.RHS, firstT, cfg);
    cout << "first set for RHS: ";
    for (string s : first.F)
    {
        cout << s << " ";
    }
    cout << endl;

    set<string> followT;
    FollowResult follow = followSet(rule.LHS, followT, cfg);
    cout << "follow set for LHS: ";
    for (string s : follow.F)
    {
        cout << s << " ";
    }
    cout << endl;

    if (first.F.empty())
    {
        cout << "Computed by: FollowSet(LHS)" << endl;
        predict = follow.F;
    }
    else 
    {
        cout << "Computed by: FirstSet(RHS)" << endl;
        predict = first.F;
    }

    return predict;
}

#endif