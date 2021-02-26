#ifndef LIST_H_DTL
#define LIST_H_DTL

#include <vector>
#include <string>

using namespace std;

bool derivesToLambda(string L)
{
    if (L == "S")
    {
        return false;
    }
    else if (L == "A")
    {
        return false;
    }
    else if (L == "B")
    {
        return true;
    }
    else if (L == "C")
    {
        return false;
    }
    return false;
}

#endif