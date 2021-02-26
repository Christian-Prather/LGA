#ifndef LIST_H_FOLLOW
#define LIST_H_FOLLOW

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
