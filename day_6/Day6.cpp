//
// Created by pimvanleeuwen on 11/10/24.
//

#include "Day6.h"

#include <iostream>
#include <sstream>

using namespace std;

void Day6::part_1(const vector<string> &lines) {
    // fish, grouped by fish added at the same time (if we add 200 fish at the same time we just make a tuple of (200,8)
    // instead of going over all fish
    vector<vector<long> > fish;

    // process the input
    stringstream ss(lines[0]);
    string token;

    // separate line
    while (getline(ss, token, ',')) {
        fish.push_back({1, stoi(token)});
    }

    // starting day
    int day = 0;

    // go through all 256 days
    while (day < 256) {
        // the amount of fish to add
        long to_add = 0;

        // decrease all the fish and count what to add
        for (auto &i: fish) {
            if (i[1] == 0) {
                to_add += i[0];
            }

            i[1] = (i[1] == 0) ? 6 : i[1] - 1;
        }

        // add all the fish in one go
        fish.push_back({to_add, 8});

        // output on the part 1 interval
        if (day == 79) {
            long fish_count = 0;
            for (vector<long> f: fish) {
                fish_count += f[0];
            }
            cout << "Part 1: " << fish_count << endl;
        }

        day++;
    }

    // output on the 256 days interval
    long fish_count = 0;
    for (vector<long> f: fish) {
        fish_count += f[0];
    }
    cout << "Part 2: " << fish_count << endl;
}

void Day6::part_2(const vector<string> &lines) {
}
