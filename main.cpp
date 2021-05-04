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
#include <map>

//#include "include/cfg.h"
#include "include/derivesToLambda.h"
#include "include/predict.h"
#include "include/first.h"
//#include "include/ll-table.h"
//#include "include/item.h"
//#include "include/closure.h"
//#include "include/goTo.h"
#include "include/actionTable.h"
//#include "include/ll-tabular-parsing.h"
#include "include/regex.h"
#include "include/parser.h"

using namespace std;
string tokensHex;
vector<vector<string>> inputRows;

void loadScanFile(string filePath)
{
    bool firstLine = true;

    string line;
    ifstream inputFile(filePath);
    if (!inputFile)
    {
        exit(1);
    }
    while (getline(inputFile, line))
    {
        if (line.empty())
        {
            continue;
        }

        if (firstLine)
        {
            firstLine = false;
            tokensHex = line;
            continue;
        }

        // vector<string> row;
        // string word = "";
        // char lastCharacter;
        // cout << line << endl;
        // for (auto character : line)
        // {
        //     if (character == ' ' && lastCharacter != ' ')
        //     {
        //         row.push_back(word);
        //         word = "";
        //     }
        //     else if (character != ' ')
        //     {
        //         word += character;
        //         lastCharacter = character;
        //     }
        // }

        vector<string> row;
        istringstream ss(line);
        for (string s; ss >> s;)
        {
            row.push_back(s);
        }
        inputRows.push_back(row);
    }
    inputFile.close();
}

int main(int argc, char **argv)
{
    //string inputFile = "../scan.lut";
    //string outputFile = "../scan.u";
    string inputFile = "";
    string outputFile = "";
    if (argc > 2)
    {
        inputFile = argv[1];
        outputFile = argv[2];
    }
    else
    {
        cout << "Not enough arguments " << endl;
        exit(1);
    }
    string grammarFile = "../testFiles/llre.cfg";
    loadScanFile(inputFile);
    for (auto row : inputRows)
    {
        for (auto item : row)
        {
            cout << item << " ";
        }
        cout << endl;
    }
    CFG cfg = readCfg(grammarFile);
    printOutput(cfg);

    stack<Rule> T;
    for (string nonTerm : cfg.nonTerminals)
    {
        cout << nonTerm << " : " << endl;

        bool dToL = derivesToLambda(nonTerm, T, cfg);
        string lambda = "false";
        if (dToL == true)
        {
            lambda = "true";
        }
        cout << "Derives to lambda: " << lambda << endl;

        vector<string> XB;
        XB.push_back(nonTerm);
        set<string> firstT;
        FirstResult first = firstSet(XB, firstT, cfg);
        cout << "First set: ";
        for (string f : first.F)
        {
            cout << f << " ";
        }
        cout << endl;

        set<string> followT;
        FollowResult follow = followSet(nonTerm, followT, cfg);
        cout << "Follow set: ";
        for (string f : follow.F)
        {
            cout << f << " ";
        }
        cout << endl
             << endl;
    }

    for (Rule rule : cfg.rules)
    {
        cout << rule.LHS << " -> ";
        for (string s : rule.RHS)
        {
            cout << s << " ";
        }
        cout << ": " << endl;

        set<string> predict = predictSet(rule, cfg);
        cout << "predict set: ";
        for (string s : predict)
        {
            cout << s << " ";
        }
        cout << endl;
        cout << "Rule #: " << rule.identity << endl;
        cout << endl;
    }

    Table llTable = buildTable(cfg);

    // vector<Item> vecItem;
    // for (Rule r : cfg.rules)
    // {
    //     if (r.LHS == cfg.startSymbol)
    //     {
    //         Item t;
    //         t.rule = r;
    //         t.progressMarkerIndex = 0;
    //         vecItem.push_back(t);
    //     }
    // }

    // ItemSet itemSet;
    // itemSet.itemSet = vecItem;
    // itemSet.parentItemSetGrammarSymbol = cfg.startSymbol;

    // cout << "Original Item Set:\n";
    // printItemSet(itemSet);
    // cout << "Item Set After Closure:\n";
    // itemSet = closure(itemSet, cfg);
    // itemSet.index = 0;
    // printItemSet(itemSet);

    // vector<ItemSet> itemSets;
    // itemSets.push_back(itemSet);

    // struct Graph
    // {
    //     int pointsTo;
    //     string symbol;
    // };
    // map<int, vector<Graph>> itemSetMap;

    // set<int> doneSets;
    // // Combine sets
    // vector<string> symbols;
    // for (string s : cfg.terminals)
    // {
    //     symbols.push_back(s);
    // }
    // symbols.push_back("$");
    // for (string s : cfg.nonTerminals)
    // {
    //     if (s != cfg.startSymbol)
    //     {
    //         symbols.push_back(s);
    //     }
    // }

    // int setSize;
    // while (itemSets.size() != setSize)
    // {
    //     setSize = itemSets.size();
    //     for (int i = 0; i < setSize; i++)
    //     {
    //         ItemSet set = itemSets.at(i);
    //         if (doneSets.find(set.index) == doneSets.end())
    //         {
    //             for (string symbol : symbols)
    //             {
    //                 ItemSet newSet = goTo(set, symbol, cfg);
    //                 int gotoSetIndex = searchSets(itemSets, newSet);
    //                 if (gotoSetIndex == -1)
    //                 {
    //                     if (!newSet.itemSet.empty())
    //                     {
    //                         newSet.index = itemSets.size();
    //                         itemSets.push_back(newSet);

    //                         Graph graphEntry;
    //                         graphEntry.pointsTo = newSet.index;
    //                         graphEntry.symbol = symbol;
    //                         itemSetMap[set.index].push_back(graphEntry);
    //                     }
    //                 }
    //                 else
    //                 {
    //                     Graph graphEntry;
    //                     graphEntry.pointsTo = gotoSetIndex;
    //                     graphEntry.symbol = symbol;
    //                     itemSetMap[set.index].push_back(graphEntry);
    //                 }
    //             }
    //             doneSets.insert(set.index);
    //         }
    //     }
    // }

    // cout << "GOTO:///////////////////////////////" << endl;
    // for (auto set : itemSets)
    // {
    //     printItemSet(set);
    // }

    // auto actionTable = buildActionTable(itemSets, cfg, symbols);
    // printActionTable(actionTable, symbols);

    //string regex_input = "a-d.q(A|B|)*de+";
    for (auto row : inputRows)
    {

        cout << row[0];
        auto regex_tokens = scan_regex(row[0]);

        Node rootTree = buildRawParseTree(cfg, llTable, regex_tokens);
        //cout << rootTree.type << endl;
    }

    ofstream outFile;
    outFile.open(outputFile);
    outFile << tokensHex << '\n';
    for (auto row : inputRows)
    {
        string name = row[1];
        name += ".tt";
        outFile << name;
        outFile << " ";
        outFile << row[1];
        if (row.size() == 3)
        {
            outFile << " ";
            outFile << row[2];
        }
        outFile << '\n';
    }

    //auto root = LLTabularParsing()
    return 0;
}