#ifndef LL_TABLE_H
#define LL_TABLE_H

#include <vector>
#include <string>
#include <map>
using namespace std;

#define NA 0

// struct TableRow
// {
//     map<string, vector<int>> entry;
// };

struct Table
{
    vector<string> headerRow;
    map<string, vector<int>> rows;
};

#endif