//
// Created by pimvanleeuwen on 11/8/24.
//

#include "Day1.h"

#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>
using namespace std;

void Day1::part_1(const vector<string>& lines) {

    vector<int> nums;
    nums.reserve(lines.size());

    for (const string& line : lines) {
        nums.push_back(stoi(line));
    }

    // two counters for part 1 and part 2
    int increasing_part_1 = 0;
    int increasing_part_2 = 0;

    // count window size 1 and window size 3
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] > nums[i-1]) {
            ++increasing_part_1;
        }

        if (i > 2 && (nums[i-1]+nums[i-2]+nums[i] > nums[i-1]+nums[i-2]+nums[i-3])) {
            ++increasing_part_2;
        }
    }

    // output the results
    cout << "Part 1: " << increasing_part_1 << endl;
    cout << "Part 2: " << increasing_part_2 << endl;
}

void Day1::part_2(const vector<string>& lines) {
    cout << "Done already" << endl;
}
