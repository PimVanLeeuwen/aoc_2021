//
// Created by pimvanleeuwen on 11/13/24.
//

#include "Day13.h"

#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>

using namespace std;

void Day13::execute(const vector<string> &lines) {
    set<pair<int, int>> positions;
    vector<pair<string, int>> instructions;
    bool instructions_started = false;

    size_t part_1 = -1;

    // Convert all the instructions to the variables
    for (const auto &line : lines) {
        if (line.empty()) {
            instructions_started = true;
        } else if (!instructions_started) {
            stringstream ss(line);
            string token;
            int x = -1;

            while(getline(ss, token, ',')) {
                if (x == -1) {
                    x = stoi(token);
                } else {
                   positions.emplace(x,stoi(token));
                }
            }

        } else {
            stringstream ss(line);
            string token;
            string dim = "a";

            while(getline(ss, token, '=')) {
                if (dim == "a") {
                    dim = token;
                } else {
                    instructions.emplace_back(dim,stoi(token));
                }
            }
        }
    }

    for (const auto &[dim, amount] : instructions) {
        // set for after the fold, duplicated will automatically be removed
        set<pair<int, int>> new_positions;

        // fold the paper
        if (dim == "x") {
            for (auto &pos : positions) {
                if (pos.first > amount) {
                    new_positions.emplace(pos.first - 2*(pos.first - amount), pos.second);
                } else {
                    new_positions.insert(pos);
                }
            }
        } else {
            for (auto &pos : positions) {
                if (pos.second > amount) {
                    new_positions.emplace(pos.first, pos.second - 2*(pos.second - amount));
                } else {
                    new_positions.insert(pos);
                }
            }
        }

        // place the new positions back
        positions = new_positions;


        // print part 1
        if (part_1 == -1) {
            part_1 = positions.size();
            cout << "Part 1: " << part_1 << endl;
        }

    }

    // get the range for the print
    int max_y = -1;
    int max_x = -1;
    for (const auto &[x, y] : positions) {
        max_y = max(max_y, y);
        max_x = max(max_x, x);
    }
    cout << "Part 2: "<< endl;
    for (int y = 0; y <= max_y; y++) {
        for (int x = 0; x <= max_x; x++) {
            if (positions.count(pair(x, y)) == 1) {
                cout << "#";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }


    

}
