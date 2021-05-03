#include "include/derivesToLambda.h"

bool prodRuleIsInStack(Rule p, stack<Rule> T)
{
    stack<Rule> T_copy = T;

    while ((!T_copy.empty()) && (T_copy.top().LHS != p.LHS) && (T_copy.top().RHS != p.RHS))
    {
        T_copy.pop();
    }
    if (!T_copy.empty())
    {
        return true;
    }
    return false;
}

bool derivesToLambda(string L, stack<Rule> T, CFG cfg)
{
    // foreach ( p ∈ P with LHS L )
    for (Rule p : cfg.rules)
    {
        if (p.LHS == L)
        {
            if (prodRuleIsInStack(p, T))
            {
                continue;
            }
            if (p.RHS[0] == "lambda")
            {
                return true;
            }
            bool allderivelambda = true;
            // foreach ( Xi ∈ N in RHS of p )
            for (string X : p.RHS)
            {
                if (X == "$")
                {
                    continue;
                }
                if (find(cfg.terminals.begin(), cfg.terminals.end(), X) != cfg.terminals.end())
                {
                    goto cont;
                }
                T.push(p);

                allderivelambda = derivesToLambda(X, T, cfg);

                T.pop();

                if (!allderivelambda)
                {
                    break;
                }
            }
            if (allderivelambda)
            {
                return true;
            }
        }
    cont:;
    }
    return false;
}