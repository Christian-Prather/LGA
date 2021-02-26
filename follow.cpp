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

#include "include/follow.h"
using namespace std;

/**
 * @brief Set the Union object
 * 
 * @param first 
 * @param second 
 * @return set<string> 
 */
set<string> setUnion(set<string> first, set<string> second)
{
    set<string> result = first;
    for (auto x : second)
    {
        if (!result.count(x))
        {
            result.insert(x);
        }
    }
    return result;
}

/**
 * @brief Placeholder
 * 
 * @param L 
 * @return true 
 * @return false 
 */
bool derivesToLambda(string L)
{
    if (L == "S")
    {
        return false;
    }
    else if (L == "A")
    {
        return false;
    }
    else if (L == "B")
    {
        return true;
    }
    else if (L == "C")
    {
        return false;
    }
    return false;
}

/**
 * @brief Recursivly find the follow set
 * 
 * @param sequence 
 * @param T 
 * @return FollowResult 
 */
FollowResult firstSet(string sequence, set<string> T)
{
    set<string> F;
    char next = sequence.at(0);
    string x;
    x += next;

    FollowResult result;
    if (T.count(x))
    {
        T.insert(x);
        // Get all rules where LHS match x
        for (auto rule : rules)
        {
            if (rule.lhs == x)
            {
                FollowResult tempResult = firstSet(rule.rhs, T);
                result.F = setUnion(F, tempResult.F);
            }
        }
    }

    if (derivesToLambda(x))
    {
        sequence.erase(sequence.begin());
        FollowResult tempResult = firstSet(sequence, T);
        result.F = setUnion(F, tempResult.F);
    }
    result.T = T;
    return result;
}
