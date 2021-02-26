#include <fstream>
#include <sstream>
#include <iostream>

#include "cfg.h"

using namespace std;

/***
 * IsStrLowercase(string)
 * Given a string s, return true if it is lowercase
 */
bool IsStrLowercase(string s) {
    for (char c : s) {
        if (!islower(c)) return false;
    }
    return true;
}

/***
 * ReadFile(string)
 * Given a filename (string) file, read the file into a CFG struct and return the CFG
 */
CFG ReadFile(string file) {
    CFG cfg; // CFG to return
    string line;
    ifstream f(file);

    // If we successfully opened the file
    if (f.is_open()) {

        int ruleIdx = -1;
        // For each line in the file
        while (getline(f,line)) {

            // Read the line into a vector of strings lineVec
            stringstream ss(line);
            vector<string> lineVec;
            while(!ss.eof()) {
                string temp;
                ss >> temp;
                if (temp != "\0") lineVec.push_back(temp);
            }

            vector<string> rightSide;
            bool right = false; 

            // Check if the first character on the line is |
            // If so, set right to true and remove the | from the line         
            if (lineVec.at(0) == "|") {
                right = true;
                lineVec.erase(lineVec.begin());
            }

            // Loop through the line vector
            for (int i = 0; i < lineVec.size(); i++) {

                // Once we hit a ->
                if (lineVec.at(i) == "->") {
                    CFGRule rule; // create a new cfg rule
                    rule.nonTerminal = lineVec.at(i-1); // add the non-terminal to the rule
                    cfg.nonTerminals.insert(lineVec.at(i-1)); // add the non-terminal to the CFG                 
                    right = true; // we are now on the right side of this rule
                    cfg.grammarRules.push_back(rule); // add the rule to the cfg
                    ruleIdx++;
                    continue;
                }

                // If we are on the right side of the rule
                if (right == true) {
                    rightSide.push_back(lineVec.at(i)); // add the rest of the line to vect rightSide
                }
            }

            vector<string> ruleProd; // vector to hold the current production
            // Loop through the right side of the rule
            for (int i = 0; i < rightSide.size(); i++) {

                // check if the symbol is a terminal
                if (IsStrLowercase(rightSide.at(i)) &&
                                   rightSide.at(i) != "lambda" &&
                                   rightSide.at(i) != "|") {
                    cfg.terminals.insert(rightSide.at(i)); // If yes, add to the cfg
                }

                // Check if this is the start state
                if (rightSide.at(i) == "$") {
                    cfg.startSymbol = cfg.grammarRules.at(ruleIdx).nonTerminal; // If yes, set cfg startState
                }

                // Push back symbol to rule production
                if (rightSide.at(i) != "|") {
                    ruleProd.push_back(rightSide.at(i));
                }

                // If we encounter a | in the middle of a line, push the old production to the
                // cfg and start a new rule production
                else {
                    cfg.grammarRules.at(ruleIdx).productions.push_back(ruleProd);
                    ruleProd.clear();
                }
            }
            cfg.grammarRules.at(ruleIdx).productions.push_back(ruleProd); // Push the last rule production to the cfg
        }
    
        f.close(); // Close file
    }

    else cout << "Unable to open file.\n";

    return cfg;
}

/***
 * PrintCFG(CFG)
 * Given a CFG, print the CFG in Prof Hellman's format
 */
void PrintCFG(CFG cfg) {

    // Print terminals
    cout << "Terminals:";
    for (string s : cfg.terminals) {
        cout << " " << s;
    }
    cout << endl;

    // Print non-terminals
    cout << "Non-terminals:";
    for (string s : cfg.nonTerminals) {
        cout << " " << s;
    }
    cout << endl << endl;

    // Print grammar rules
    cout << "Grammar Rules\n";
    int lineNum = 1;

    // Sorry about this triple for loop... I got a little vector-happy with my structs

    // For each rule
    for (int i = 0; i < cfg.grammarRules.size(); i++) {
        // For each rule production
        for (int j = 0; j < cfg.grammarRules.at(i).productions.size(); j++) {

            // Print the line num, the non-terminal, and ->
            cout << "(" << to_string(lineNum) << ")\t" << cfg.grammarRules.at(i).nonTerminal << " -> ";

            // For each string/symbol in the current production
            for (int k = 0; k < cfg.grammarRules.at(i).productions.at(j).size(); k++) {
                cout << cfg.grammarRules.at(i).productions.at(j).at(k) << " "; // Print the symbol
            }
            cout << endl;
            lineNum++;
        }
    }

    // Print CFG start state
    cout << "\nGrammar Start Symbol or Goal: " << cfg.startSymbol << endl;

}