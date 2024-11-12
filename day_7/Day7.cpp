//
// Created by pimvanleeuwen on 11/10/24.
//

#include "Day7.h"

#include <algorithm>
#include <iostream>
#include <limits.h>
#include <sstream>

using namespace std;

void Day7::part_1(const vector<string> &lines) {
    vector<int> positions;

    // process the input
    stringstream ss(lines[0]);
    string token;

    // separate line
    while (getline(ss, token, ',')) {
        positions.push_back(stoi(token));
    }

    // for part 1 we just need the median
    sort(positions.begin(), positions.end());

    // count the fuel consumption from this median
    int sum = 0;

    for (const int i : positions) {
        sum += abs(i - positions[positions.size()/2]);
    }

    cout << "Part 1: " << sum << endl;

    // part 2 is NP-hard so brute force (geometric median finding)
    sum = 0;

    // just try for each possible combination and update best result (this is still pretty fast)
    long min_fuel = LONG_MAX;

    for (const int i : positions) {
        long fuel = 0;
        for (const int j : positions) {
            fuel += ((abs(i - j) * (abs(j - i) + 1))/2);
        }
        min_fuel = min(min_fuel, fuel);
    }

    cout << "Part 2: " << min_fuel << endl;
}

void Day7::part_2(const vector<string> &lines) {
}
