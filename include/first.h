#ifndef LIST_H_FIRST
#define LIST_H_FIRST

/**
 * @file first.h
 * @author Christian Prather
 * @brief Helper functions for first set
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "setUnion.h"
#include "derivesToLambda.h"
#include "cfg.h"

#include <string>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct FirstResult
{
    set<string> F;
    set<string> T;
};

FirstResult firstSet(vector<string> XB, set<string> T, vector<Rule> cfg);

#endif
