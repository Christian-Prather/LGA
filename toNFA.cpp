#include "include/toNFA.h"

int TreeNFA::addState()
{
    vector<int> newRow(this->header.size(), -1);
    this->T[this->stateCounter] = newRow;
    this->stateCounter++;
    return this->stateCounter;
}

void TreeNFA::addEdge(string character, int src, int dest)
{
}

void TreeNFA::addLambda(int src, int dest)
{
}

int TreeNFA::characterColumn(string character)
{
    for (int i = 0; i < this->header.size(); i++)
    {
        if (this->header[i] == character)
        {
            return i;
        }
    }
    return -1; // Not valid character
}

TreeNFA::TreeNFA()
{
    // Initialize with 0,1 states
}

// void TreeNFA::nodeSeq(int src, int dest)
// {
//     int childdest = 0;
//     for (auto child : this->currentNode->children)
//     {
//         childdest = this->addState();
//         child.process(src, childdest);
//         src = childdest;
//     }
//     addLambda(childdest, dest);
// }

// void nodeRange(int src, int dest)
// {
//     vector<string> charRange = getCharRange(string start, string end);
//     for (auto character : charRange)
//     {
//         addEdge(character, src, dest);
//     }
// }

// void nodeDot(int src, int dest)
// {
//     for (auto charcter : header)
//     {
//         addEdge(character, src, dest);
//     }
// }


