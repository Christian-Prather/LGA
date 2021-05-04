#include "include/derivesToLambda.h"

bool allderivelambda = true;

bool prodRuleIsInStack(Rule p, stack<Rule> T)
{
    auto T_copy = T;
    while (!T_copy.empty())
    {
        auto rule = T_copy.top();
        T_copy.pop();
        if (rule.LHS == p.LHS && rule.RHS == p.RHS)
        {
            return true;
        }
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
            // foreach ( Xi ∈ N in RHS of p )
            for (string X : p.RHS)
            {
                if (X == "$")
                {
                    goto cont;
                }
                if (find(cfg.terminals.begin(), cfg.terminals.end(), X) != cfg.terminals.end())
                {
                    goto cont;
                }
            }

            allderivelambda = true;
            for (string X : p.RHS)
            {
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