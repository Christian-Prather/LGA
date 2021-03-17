//
// Created by Connor Barnes on 3/17/21.
//

#ifndef LGA_CLOSURE_H
#define LGA_CLOSURE_H

#include "item.h"

/**
 * @brief Determines the closure of the given item set in the given grammar.
 *
 * @param initial The item set to find the closure of.
 * @param grammar The CFG that the item set is apart of.
 * @return The closure of the given item set in the given grammar.
 */
ItemSet closure(ItemSet initial, CFG grammar)
{
    auto prev = initial;
    auto copy = initial;

    if (initial.itemSet.empty()) {
        return initial;
    }

    set<string> added;
    // The nonterminals we have already added so we don't re-add them
    added.insert(initial.itemSet[0].rule.LHS);

    do {
        prev = copy;

        for (Item item : prev.itemSet) {
            if (item.rule.RHS.size() > item.progressMarkerIndex) {
                // Not on last
                if (isupper(item.rule.RHS[item.progressMarkerIndex][0])) {
                    // Is nonterminal
                    auto nonterminal = item.rule.RHS[item.progressMarkerIndex];

                    if (added.find(nonterminal) != added.end()) {
                        // Already added fresh starts for this nonterminal
                        continue;
                    }

                    added.insert(nonterminal);

                    for (auto rule : grammar.rules) {
                        if (rule.LHS == nonterminal) {
                            Item next;
                            next.rule = rule;
                            next.progressMarkerIndex = 0;
                            copy.itemSet.push_back(next);
                        }
                    }
                }
            }
        }
    } while (prev.itemSet.size() != copy.itemSet.size());

    return prev;
}

/**
 * @brief A testing function that allows for a nonterminal and a CFG to be passed in to determine
 * the closure set more easily.
 *
 * @param nonterminal The nonterminal to use as the initial item set.
 * @param cfg The grammar that the item set should be in.
 * @return The closure of the item set made up of all rules with a LHS equal to nonterminal.
 */
ItemSet testClosure(string nonterminal, CFG cfg)
{
    ItemSet test;
    test.parentItemSetGrammarSymbol = nonterminal;

    for (auto rule : cfg.rules) {
        if (rule.LHS == nonterminal) {
            Item item;
            item.progressMarkerIndex = 0;
            item.rule = rule;

            test.itemSet.push_back(item);
        }
    }

    auto result = closure(test, cfg);
    return result;
}


#endif //LGA_CLOSURE_H
