#ifndef LIST_H_FIRST
#define LIST_H_FIRST

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
