<<<<<<< HEAD:first.cpp
/**
 * @file follow.cpp
 * @author Christian Prather
 * @brief Follow function
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "include/first.h"
using namespace std;
=======
#include "include/follow.h"
>>>>>>> follow:follow.cpp

FollowResult followSet(string A, set<string> T, CFG cfg)
{
    FollowResult followResult;

    if (T.find(A) == T.end())
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
                else
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
