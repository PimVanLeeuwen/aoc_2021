//
// Created by pimvanleeuwen on 11/13/24.
//

#include "Day14.h"

#include <algorithm>
#include <iostream>
#include <limits.h>
#include <map>
#include <set>
#include <sstream>

using namespace std;

void Day14::execute(const vector<string> &lines) {

    constexpr int STEPS = 40;
    map<string, long> pairs;
    map<string, char> rules;

    // convert the input
    for (auto &line : lines) {
        if (pairs.empty()) {
            for (int j = 1; j < line.size(); j++) {
                string duo;
                duo += line[j-1];
                duo += line[j];
                pairs[duo] = (pairs[duo] > 0) ? pairs[duo]++ : 1;
            }
        } else if (!line.empty()) {
            rules[line.substr(0, 2)] = line.substr(6).c_str()[0];
        }
    }

    // for each pair we add the new characters and generate the new pairs.
    // by keeping track of the pairs we do not get the exponential large string and only have to process each distinct
    // pair once
    for (int i = 0; i < STEPS; i++) {
        map<string, long> new_pairs;
        // so pair PF becomes pair PP and PF
        for (const auto&[pair, amount] : pairs) {
            char target = rules[pair];
            string pair_first;
            pair_first += pair[0];
            pair_first += target;
            new_pairs[pair_first] = (new_pairs[pair_first] > 0) ? new_pairs[pair_first] += amount : amount;

            string pair_second;
            pair_second += target;
            pair_second += pair[1];
            new_pairs[pair_second] = (new_pairs[pair_second] > 0) ? new_pairs[pair_second] += amount : amount;
        }

        pairs = new_pairs;

        if (i == 9 || i == 39) {
            map<char, long> counts_2;

            // count all the chars
            for (const auto&[pair, amount] : pairs) {
                counts_2[pair[0]] = (counts_2[pair[0]] > 0) ? counts_2[pair[0]] += amount : amount;
                counts_2[pair[1]] = (counts_2[pair[1]] > 0) ? counts_2[pair[1]] += amount : amount;
            }

            // we count everything double except one for these two as they are at the start and end, so add them
            counts_2['B']++;
            counts_2['K']++;

            long max_num = 0;
            long min_num = LONG_MAX;

            for (const auto&[c, amount] : counts_2) {
                max_num = max(max_num, (amount/2));
                min_num = min(min_num, (amount/2));
            }

            if (i == 9) {
                cout << "Part 1: " << max_num - min_num << endl;
            } else {
                cout << "Part 2: " << max_num - min_num << endl;
            }

        }
    }
}
