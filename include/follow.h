#ifndef LIST_H_FOLLOW
#define LIST_H_FOLLOW

/**
 * @file follow.h
 * @author Alexandra Ernst
 * @brief 
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "first.h"
#include "cfg.h"
#include "setUnion.h"

#include <set>
#include <string>
#include <iostream>

using namespace std;

struct FollowResult
{
    set<string> F;
    set<string> T;
};

FollowResult followSet(string A, set<string> T, vector<Rule> cfg);

#endif
