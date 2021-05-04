#ifndef LIST_H_FOLLOW
#define LIST_H_FOLLOW


#include <set>
#include <string>
#include <iostream>
#include "cfg.h"

using namespace std;

struct FollowResult
{
    set<string> F;
    set<string> T;
};

FollowResult followSet(string A, set<string> T, CFG cfg);
bool checkAllLambda(vector<string> XB, CFG cfg);
#endif
