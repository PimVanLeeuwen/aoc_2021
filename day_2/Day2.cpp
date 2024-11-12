//
// Created by pimvanleeuwen on 11/8/24.
//

#include "Day2.h"

#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>
using namespace std;

void Day2::execute(const vector<string>& lines) {

    int aim = 0;
    int x = 0;
    int z = 0;
    int z_2 = 0;

    for (string line : lines) {
        string move = line.substr(0, line.find(' '));
        line.erase(0, line.find(' ') + 1);
        const int amount = stoi(line);

        if (move == "up") {
            z -= amount;
            aim -= amount;
        } else if (move == "down") {
            z += amount;
            aim += amount;
        } else {
            x += amount;
            z_2 += aim*amount;
        }

    }

    // output the results
    cout << "Part 1: " << x*z << endl;
    cout << "Part 2: " << x*z_2 << endl;
}
