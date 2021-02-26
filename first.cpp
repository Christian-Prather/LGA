#include "include/first.h"

FirstResult firstSet(vector<string> XB, set<string> T, vector<Rule> cfg)
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
        for (Rule rule : cfg)
        {
            if (rule.LHS == x)
            {
                FirstResult tempResult = firstSet(rule.RHS, T, cfg);
                result.F = setUnion(F, tempResult.F);
            }
        }
    }

    if (derivesToLambda(x))
    {
        XB.erase(XB.begin());
        FirstResult tempResult = firstSet(XB, T, cfg);
        result.F = setUnion(F, tempResult.F);
    }
    result.T = T;
    return result;
}