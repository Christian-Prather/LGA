#ifndef LL_TABLE_H
#define LL_TABLE_H

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "cfg.h"

using namespace std;

#define NA 0

struct Table
{
    vector<string> headerRow;
    map<string, vector<int>> rows;
};

Table buildTable(CFG cfg);

#endif