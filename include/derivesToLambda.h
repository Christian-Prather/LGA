#ifndef LIST_H_DTL
#define LIST_H_DTL

#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

#include "cfg.h"

bool prodRuleIsInStack(Rule p, stack<Rule> T);

bool derivesToLambda(string L, stack<Rule> T, CFG cfg);
#endif