#ifndef LIST_H_DTL
#define LIST_H_DTL

#include <vector>
#include <string>
#include <stack>

using namespace std;

#include "cfg.h"

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

    // Vector of rules that have L as their LHS
    vector<Rule> lRules;
    for (Rule p : cfg.rules)
    {
        if (p.LHS == L)
        {
            lRules.push_back(p);
            break;
        }
    }

    // foreach ( p ∈ P with LHS L )
    for (Rule p : lRules)
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
            if (cfg.terminals.find(X) != cfg.terminals.end())
            {
                continue;
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
    return false;
}

#endif