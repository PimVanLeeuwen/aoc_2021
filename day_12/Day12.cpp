//
// Created by pimvanleeuwen on 11/13/24.
//

#include "Day12.h"

#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <sstream>

using namespace std;

// return if a string is an uppercase or not
bool is_uppercase(const string& s) {
    return (all_of(s.begin(), s.end(), [](const char c) {
        return isupper(c);
    }));
}

void Day12::execute(const vector<string> &lines) {
    map<string, vector<string>> cave_map;

    int part_1 = 0;
    int part_2 = 0;

    // add all of the directions
    for (const auto &line : lines) {

        stringstream ss(line);
        string token;

        vector<string> tokens;

        while(getline(ss, token, '-')) {
            tokens.push_back(token);
        }

        // add both ways to the cave map since edges are bidirectional
        if (cave_map.count(tokens[0])) {
            cave_map[tokens[0]].push_back(tokens[1]);
        } else {
            cave_map[tokens[0]] = {tokens[1]};
        }

        if (cave_map.count(tokens[1])) {
            cave_map[tokens[1]].push_back(tokens[0]);
        } else {
            cave_map[tokens[1]] = {tokens[0]};
        }
    }

    // We keep track of a boolean to check if we visited a node twice already
    deque<pair<vector<string>, bool>> to_visit = {{{"start"}, false}};

    while (!to_visit.empty()) {
        // fetch a current path
        auto current_path = to_visit.front().first;
        auto current_double = to_visit.front().second;
        to_visit.pop_front();
        // find all possible roads to take (for now)
        for (const auto& possible_next : cave_map[current_path.back()]) {
            // we do not go back to start
            if (possible_next == "start") {
                continue;
                // end marks the end of this path
            } if (possible_next == "end") {
                // if we did not use a double node it counts for part 1
                if (!current_double) {
                    part_1++;
                }
                // it always counts for part 2
                part_2++;
            } else if (is_uppercase(possible_next) ||
                count(current_path.begin(), current_path.end(), possible_next) == 0) {
                // if it is uppercase we can always go there, otherwise check if already present
                vector<string> new_path = current_path;
                new_path.push_back(possible_next);
                to_visit.emplace_back(new_path, current_double);
            } else if (!current_double) {
                // for part 2 we get one out-of-jail card for visiting a lower-case node twice.
                vector<string> new_path = current_path;
                new_path.push_back(possible_next);
                to_visit.emplace_back(new_path, true);
            }
        }
    }

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}