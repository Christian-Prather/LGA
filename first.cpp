#include "include/first.h"

#include "include/setUnion.h"
#include "include/derivesToLambda.h"

FirstResult firstSet(vector<string> XB, set<string> T, CFG cfg)
{
    string X = XB.at(0);
    set<string> F;
    FirstResult result;

    if (cfg.terminals.find(X) != cfg.terminals.end())
    {
        F.insert(X);
        result.F = F;
        return result;
    }

    if (T.find(X) == T.end())
    {
        T.insert(X);

        for (Rule p : cfg.rules)
        {
            if (p.LHS == X)
            {
                FirstResult tempFirst = firstSet(p.RHS, T, cfg);
                result.F = setUnion(result.F, tempFirst.F);
            }
        }
    }
    stack<Rule> t;
    if (derivesToLambda(X, t, cfg))
    {
        XB.erase(XB.begin());
        if (!XB.empty())
        {
            if (XB.size() == 1 && XB.at(0) != "$")
            {
                FirstResult tempFirst = firstSet(XB, T, cfg);
                result.F = setUnion(result.F, tempFirst.F);
            }
        }
    }
    result.T = T;
    return result;
}
