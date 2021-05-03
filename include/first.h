#ifndef LIST_H_FIRST
#define LIST_H_FIRST

#include "cfg.h"

#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <stack>

using namespace std;

struct FirstResult
{
    set<string> F;
    set<string> T;
};

FirstResult firstSet(vector<string> XB, set<string> T, CFG cfg);

#endif
