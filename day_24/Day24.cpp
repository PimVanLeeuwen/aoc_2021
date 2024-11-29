//
// Created by pimvanleeuwen on 11/28/24.
//

#include "Day24.h"

#include <iostream>
#include <map>
#include <sstream>


using namespace std;

long process_model_num(const int digit, const int w, long z) {
    // this solves the instructions for a given digit, model number for that digit and z from previous exercise
    // this is possible since z is the only number that carries through here
    int add_1, add_2;
    switch (digit) {
        case 0: add_1 = 11; add_2 = 6; break;
        case 1: add_1 = 11; add_2 = 14; break;
        case 2: add_1 = 15; add_2 = 13; break;
        case 3: add_1 = -14; add_2 = 1; break;
        case 4: add_1 = 10; add_2 = 6; break;
        case 5: add_1 = 0; add_2 = 13; break;
        case 6: add_1 = -6; add_2 = 6; break;
        case 7: add_1 = 13; add_2 = 3; break;
        case 8: add_1 = -3; add_2 = 8; break;
        case 9: add_1 = 13; add_2 = 14; break;
        case 10: add_1 = 15; add_2 = 4; break;
        case 11: add_1 = -2; add_2 = 7; break;
        case 12: add_1 = -9; add_2 = 15; break;
        case 13: add_1 = -2; add_2 = 1; break;
        default: throw runtime_error("Invalid digit");
    }
    const long x = (((z % 26) + add_1) == w) == 0;
    if (digit == 3 || digit == 5 || digit == 6 || digit == 8 || digit == 11 || digit == 12 || digit == 13) { z /= 26; }
    long y = (25 * x) + 1; z*=y;
    y = (w + add_2) * x; z += y;

    return z;
}

void decrease_number(vector<int> &model) {
    int counter = model.size()-1;

    while (counter >= 0) {
        if (model[counter] == 1) {
            model[counter] = 9;
            counter--;
        } else {
            model[counter]--;
            break;
        }
    }

}

// checks if b is larger than a
bool isLarger(const vector<int> &a, const vector<int> &b) {
    for (int i = 0; i < a.size(); i++) {
        if (b[i] > a[i]) { return true; }
        if (b[i] < a[i]) { return false; }
    }
}

vector<int> solve(const int digit = 13, const int z = 0) {
    if (abs(z) > 10000) return {};
    vector<int> max_sol = {};
    for (int z_test = -5000; z_test < 5000; z_test++) {
        for (int model_test = 1; model_test < 10; model_test++) {

            if (process_model_num(digit, model_test, z_test) == z) {
                // for every possible solution check if the smaller problem has a solution (we get the largest back)
                vector<int> interim_sol;
                if (digit > 0) interim_sol = solve(digit-1, z_test);
                if (digit > 0 && interim_sol.empty()) continue;
                interim_sol.push_back(model_test);

                if (max_sol.empty() || isLarger(max_sol, interim_sol)) { max_sol = interim_sol; }
            }
        }
    }

    return max_sol;

}

void Day24::execute(const vector<string> &lines) {
    // tried backwards recursive algorithm but this is too slow
    vector<int> model = solve(13, 0);

    cout << "Part 1: ";
    for (const auto &num : model) { cout << num << "||"; }
    cout << endl;
}
