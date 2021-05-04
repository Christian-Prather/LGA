#include "include/predict.h"
#include "include/follow.h"
#include "include/first.h"
#include "include/setUnion.h"
#include "include/derivesToLambda.h"
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

    stack<Rule> T;
    if (rule.RHS[0] == "lambda" || checkAllLambda(rule.RHS, cfg))
    {
        predict = setUnion(first.F, follow.F);
    }
    else
    {
        predict = first.F;
    }

    // if (first.F.empty())
    // {
    //     cout << "Computed by: FollowSet(LHS)" << endl;
    //     predict = setUnion(follow.F, first.T);
    // }
    // else
    // {
    //     cout << "Computed by: FirstSet(RHS)" << endl;
    //     predict = first.F;
    // }

    return predict;
}