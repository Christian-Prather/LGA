#ifndef LL_TABULAR_PARSING_H
#define LL_TABULAR_PARSING_H

#include <stack>

#include "cfg.h"
#include "ll-table.h"

using namespace std;

string MARKER = "MARKER";

//declaration for new tree node
struct node  { 
    string data; 
    struct node *left; 
    struct node *right; 
}; 

// procedure LLTabularParsing ( ts, LLT , P )
struct node* LLTabularParsing(Table LLT, CFG cfg) {
// ts is a token stream with peek and pop operations
// LLT is an LL (1) parsing table as described by the text
// returns a parse tree of the sentence in ts, or FAILS when ts does not emit a sentence belonging to the grammar deriving LLT .

// Recall notationally : S is the starting symbol ( goal ) of the grammar ,
// Σ$ = Σ+{$} are the terminals of the language augmented by $,
// N are the non - terminals
// P is the production rule list of the grammar ( indexed by entries of LLT ).
vector<Rule> P = cfg.rules;

// let T be a tree with an initial root node Root
struct node *rootT = NULL; 
// let Current be a reference to a node of T
struct node* current;
struct node* parent;
// let K be a stack
stack<string> K;
// Current ← Root
current = rootT;
parent = rootT;
// push S onto K
K.push(cfg.startSymbol);
// while ( |K| > 0 ) do (
while (K.size() > 0) {
    // x ← K.pop()
    string x = K.top();
    K.pop();
    // if ( x ∈ N ) then (
    if (cfg.nonTerminals.find(x) != cfg.nonTerminals.end()) {
        // # Next token may not predict a p ∈ P
        // p ← P[LLT[x][ts.peek()]] or FAIL
        Rule p = P.front();
        // push MARKER onto K
        K.push(MARKER);
        // R ← RHS of p
        vector<string> R = p.RHS;
        // in reverse order, push the elements of R onto K
        for (int i = R.size()-1; i >=0; i--) {
            K.push(R.at(i));
        }
        // let n ← new tree node for non - terminal x
        struct node *n;
        n->data = x;
        // append n as the rightmost child of Current
        current->right = n;
        // Current ← rightmost child of Current
        parent = current;
        current = current->right;
    }
    // ) else if ( x ∈ Σ$ OR x is λ ) then (
        else if (cfg.terminals.find(x) != cfg.terminals.end() || x == "$" || x == "lambda") {
        // if ( x ∈ Σ$ ) then (
            if (cfg.terminals.find(x) != cfg.terminals.end() || x == "$") {
            // # Next token must be what is expected
            // if ( x =/= ts.peek() ) then FAIL
            
            // # Update x with the token type and source value from ts
            // x ← ts.pop()
        // )
            }
        // append x as the rightmost child of Current
        current->right->data = x;
        }
    // ) else if ( x is a MA R K E R ) then (
        else if (x == MARKER) {
        // Current ← Current.parent
        current = parent;
    // )
        }
// )
}
// # Current now points to Root which has a singular child S
// return Root’s only child
}

#endif