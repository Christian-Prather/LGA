#ifndef LIST_H_FOLLOW
#define LIST_H_FOLLOW

#include "first.h"

#include <set>
#include <string>
#include <iostream>

using namespace std;

struct FollowResult
{
    set<string> F;
    set<string> T;
};

bool checkForTerminal(vector<string> XB, CFG cfg)
{
    for (string X : XB)
    {
        if (cfg.terminals.find(X) != cfg.terminals.end())
        {
            return true;
        }
    }
    return false;
}

bool checkAllLambda(vector<string> XB, CFG cfg)
{
    for (string C : XB)
    {
        stack<Rule> T;
        if (!derivesToLambda(C, T, cfg))
        {
            return false;
        }
    }
    return true;
}

FollowResult followSet(string A, set<string> T, CFG cfg)
{
    FollowResult followResult;

    if (T.find(A) != T.end())
    {
        followResult.T = T;
        return followResult;
    }
    T.insert(A);
    set<string> F;

    for (Rule rule : cfg.rules)
    {
        int count = 1;
        for (string s : rule.RHS)
        {
            if (A == s)
            {
                vector<string> XB;
                while (count < rule.RHS.size())
                {
                    XB.push_back(rule.RHS[count]);
                    count++;
                }
                if (!XB.empty())
                {
                    set<string> emptySet;
                    FirstResult firstResult = firstSet(XB, emptySet, cfg);
                    auto G = firstResult.F;
                    F = setUnion(F, G);
                }
                bool terminalHere = checkForTerminal(XB, cfg);
                bool allDerivesToLambda = checkAllLambda(XB, cfg);
                if ((XB.empty()) || ((!terminalHere) && (allDerivesToLambda)))
                {
                    FollowResult followtResult = followSet(rule.LHS, T, cfg);
                    auto G = followtResult.F;
                    F = setUnion(F, G);
                }

                continue;
            }
            count++;
        }
    }

    followResult.F = F;
    followResult.T = T;
    return followResult;
}

#endif
