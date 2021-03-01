/**
 * @file main.cpp
 * @author Alexandra Ernst
 * @brief LGA 13
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>

#include "include/cfg.h"
#include "include/derivesToLambda.h"
#include "include/first.h"
#include "include/follow.h"

using namespace std;

int main(int argc, char **argv)
{
    string inputFile = "../testFiles/assignlist.cfg";

    CFG cfg = readCfg(inputFile);
    printOutput(cfg);

    stack<Rule> T;
    for (string nonTerm : cfg.nonTerminals)
    {
        bool dToL = derivesToLambda(nonTerm, T, cfg);
        string lambda = "false";
        if (dToL == true)
        {
            lambda = "true";
        }
        cout << nonTerm << " derives to lambda: " << lambda << endl;

        // FirstResult first = firstSet();

        // set<string> followT;
        // FollowResult follow = followSet(nonTerm, followT, cfg);
        // cout << "Follow set for " << nonTerm << ": ";
        // for (string f : follow.T)
        // {
        //     cout << f << ", ";
        // }
    }
}