#ifndef TO_NFA_H
#define TO_NFA_H
#include <string>
#include <vector>
#include <map>
#include "parser.h"
using namespace std;

class TreeNFA
{
public:
    map<int, vector<int>> T;
    map<int, vector<int>> L;
    vector<string> header;
    int stateCounter = 2;

    Node* currentNode;

    TreeNFA();
    int addState();
    void addEdge(string character, int src, int dest);
    void addLambda(int src, int dest);
    int characterColumn(string character);
    void nodeSeq(int src, int dest);
};

#endif