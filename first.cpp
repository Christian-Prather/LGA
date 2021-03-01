#include "include/first.h"

FirstResult firstSet(vector<string> XB, set<string> T, CFG cfg)
{
    set<string> F;
    string next = XB.at(0);
    string x;
    x += next;

    FirstResult result;
    if (T.count(x))
    {
        T.insert(x);
        // Get all rules where LHS match x
        for (Rule rule : cfg.rules)
        {
            if (rule.LHS == x)
            {
                FirstResult tempResult = firstSet(rule.RHS, T, cfg);
                result.F = setUnion(F, tempResult.F);
            }
        }
    }
    stack<Rule> t;
    if (derivesToLambda(x, t, cfg))
    {
        XB.erase(XB.begin());
        FirstResult tempResult = firstSet(XB, T, cfg);
        result.F = setUnion(F, tempResult.F);
    }
    result.T = T;
    return result;
}