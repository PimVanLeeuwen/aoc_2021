//
// Created by pimvanleeuwen on 11/12/24.
//

#include "Day10.h"

#include <deque>
#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>

using namespace std;

void Day10::execute(const vector<string> &lines) {

    long part_1 = 0;
    vector<long> part_2_scores;
    long part_2 = 0;

    //openings characters
    vector<char> openings = {'(','[','{','<'};
    // map scores for part 1
    map<char, int> closing_score = {
        {')', 3},
        {']', 57},
        {'}', 1197},
        {'>', 25137},
    };
    // map scores for part 2
    map<char, int> closing_score_2 = {
        {')', 1},
        {']', 2},
        {'}', 3},
        {'>', 4},
    };
    // match brackets inner to outer
    map<char, char> closing_match = {
        {'(',')'},
        {'[',']'},
        {'{','}'},
        {'<','>'},
    };

    // add the input to the grid
    for (auto &line: lines) {
        vector<char> process;

        for (auto &c: line) {
            // if this is an opening, add it to the list
            if (find(openings.begin(), openings.end(), c) != openings.end()) {
                process.push_back(c);

            // otherwise it should match the opening bracket
            } else if (closing_match[process[process.size() - 1]] == c) {
                process.pop_back();
            // if this is also not the case, corrupt line
            } else {
                part_1 += closing_score[c];
                process.clear();
                break;
            }
        }

        // for part 2 check what we are still missing
        if (!process.empty()) {
            long part_2_local = 0;

            // reverse the remaining because we need from inner out the missing brackets
            reverse(process.begin(), process.end());
            for (auto &c: process) {
                // add the score
                part_2_local = (part_2_local*5) + closing_score_2[closing_match[c]];
            }

            // add the score to the list
            part_2_scores.push_back(part_2_local);
        }

    }

    // get the middle value out of the sorted part 2 array
    sort(part_2_scores.begin(), part_2_scores.end());
    part_2 = part_2_scores[part_2_scores.size() / 2];

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}