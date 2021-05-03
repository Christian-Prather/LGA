#ifndef LIST_H_PREDICT
#define LIST_H_PREDICT

#include <set>
#include <string>
#include "cfg.h"

using namespace std;

set<string> predictSet(Rule rule, CFG cfg);

#endif