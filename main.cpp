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

using namespace std;

struct Rule
{
    string LHS;
    vector<string> RHS;
};

vector<Rule> cfg;
set<string> terminals;
set<string> nonTerminals;
string startSymbol;

void readFile(string path)
{
    ifstream inputFile(path);
    string line;

    if (!inputFile.is_open())
    {
        cout << "not file" << endl;
        exit(1);
    }
    else if (inputFile.peek() == ifstream::traits_type::eof())
    {
        cout << "empty file" << endl;
        exit(1);
    }

    vector<string> rhs;
    string lhs;
    int lineCount = 0;
    while (getline(inputFile, line))
    {
        if (!line.empty())
        {
            istringstream ss(line);
            int wordCount = 0;
            for (string word; ss >> word;)
            {
                if ((lineCount == 0) && (wordCount == 0))
                {
                    startSymbol = word;
                    nonTerminals.insert(word);
                    lhs = word;
                    wordCount++;
                    continue;
                }

                if (word != "->")
                {
                    if (word != "|")
                    {
                        rhs.push_back(word);
                        if (all_of(word.begin(), word.end(), [](unsigned char c) { return std::isupper(c); }))
                        {
                            nonTerminals.insert(word);
                        }
                        else if (word != "lambda" && word != "$")
                        {
                            terminals.insert(word);
                        }
                    }
                    else
                    {
                        Rule rule;
                        rule.LHS = lhs;
                        for (string s : rhs)
                        {
                            rule.RHS.push_back(s);
                        }
                        cfg.push_back(rule);
                        rhs.clear();
                    }
                }
                else if (!rhs.empty())
                {
                    string newlhs = rhs.back();
                    rhs.pop_back();
                    Rule rule;
                    rule.LHS = lhs;
                    for (string s : rhs)
                    {
                        rule.RHS.push_back(s);
                    }
                    cfg.push_back(rule);
                    rhs.clear();
                    lhs = newlhs;
                }
                wordCount++;
            }
        }
        lineCount++;
    }
    Rule rule;
    rule.LHS = lhs;
    for (string s : rhs)
    {
        rule.RHS.push_back(s);
    }
    cfg.push_back(rule);
    rhs.clear();
}

void printOutput()
{
    cout << "Terminals: " ;
    for (auto terminal : terminals)
    {
        cout << terminal << ", ";
    }
    cout << endl << "Non-terminals: " ;
    for (auto nonTerminal : nonTerminals)
    {
        cout << nonTerminal << ", " ;
    }
    cout << endl << "Grammar Rules" << endl;
    for (Rule rule : cfg)
    {
        cout << rule.LHS << " -> ";
        for (auto rhs : rule.RHS)
        {
            cout << rhs << " ";
        }
        cout << endl;
    }
    cout << "Grammar Start Symbol or Goal: " << startSymbol << endl;
}

int main(int argc, char **argv)
{
    string inputFile = "../testFiles/assignlist.cfg";

    readFile(inputFile);
    
    printOutput();
}