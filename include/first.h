/**
 * @file follow.h
 * @author Christian Prather
 * @brief Helper functions for follow set
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <string>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

struct Rule
{
    string lhs;
    string rhs;
};

vector<Rule> rules;

struct FollowResult
{
    set<string> F;
    set<string> T;
};

set<string> setUnion(set<string> first, set<string> second);
FollowResult firstSet(vector<string> sequence, set<string> T);
