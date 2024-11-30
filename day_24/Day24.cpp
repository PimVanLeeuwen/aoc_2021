//
// Created by pimvanleeuwen on 11/28/24.
//

#include "Day24.h"

#include <cmath>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <sstream>


using namespace std;

set<pair<int, int>> EMPTY_SOLUTIONS;
vector<deque<int>> solutions;

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

// checks if b is larger than a
bool isLarger(const deque<int> &a, const deque<int> &b) {
    for (int i = 0; i < a.size(); i++) {
        if (b[i] > a[i]) { return true; }
        if (b[i] < a[i]) { return false; }
    }

    return false;
}

// verify that a model number actually is valid
bool verify(const deque<int> &model) {
    long z = 0;
    for (int counter = 0; counter < model.size(); counter++) {
        z = process_model_num(counter, model[counter], z);
    }

    return z == 0;
}

deque<int> solve(const int digit, const long z, const deque<int> solution_before) {
    // // branch pruning if we already know the solution
    // this gives the extreme (sub)solution for given digit and a given z.
    if (EMPTY_SOLUTIONS.find({digit, z}) != EMPTY_SOLUTIONS.end()) { return {}; }

    // construct a solution
    deque<int> extreme_sol = {};

    // check all possible options for digit here and possible z values
    for (int model_test = 1; model_test < 10; model_test++) {
        // get the new_z value
        const long new_z = process_model_num(digit, model_test, z);

        // in this case z can never come back to 0 zero again
        if (new_z > pow(26, (14 - digit)) + 100) { return {}; }

        deque<int> interim_sol;
        deque<int> solution_before_new = solution_before; solution_before_new.push_back(model_test);
        // in this case we also need the sub-solution from the next digits
        if (digit < 13) interim_sol = solve(digit+1, new_z, solution_before_new);
        // in this case there is no valid solution so we also skip this digit
        if ((digit < 13 && interim_sol.empty()) || digit == 13 && !verify(solution_before_new)) continue;
        // make the "complete" solution for the current digit
        interim_sol.push_front(model_test);

        // skip invalid solutions for the complete part
        if (digit == 13) { solutions.push_back(solution_before_new); }
        // return interim_sol;

        // keep track of the biggest one
        if (extreme_sol.empty() || isLarger(extreme_sol, interim_sol)) { extreme_sol = interim_sol; }
    }

    // if there were no solutions, this branch is impossible so we put that in the known solutions
    if (extreme_sol.empty()) EMPTY_SOLUTIONS.emplace(digit, z);
    return extreme_sol;
}

void Day24::execute(const vector<string> &lines) {
    // tried backwards recursive algorithm but this is too slow
    solve(0, 0, {});

    cout << "Part 1: "; for (const auto &num : solutions[0]) { cout << num; } cout << endl;
    cout << "Part 2: "; for (const auto &num : solutions[solutions.size()-1]) { cout << num; } cout << endl;

}
