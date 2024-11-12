//
// Created by pimvanleeuwen on 11/8/24.
//

#include "Day3.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
void Day3::execute(const vector<string>& lines) {
    auto counts = vector(12, 0);
    auto gamma = vector(12, 0);
    auto epsilon = vector(12, 0);

    for (const string& line : lines) {
        for ( int i = 0 ; i < line.length(); i++) {
            const int amount = stoi(line.substr(i, 1));
            counts[i] += amount;
        }
    }

    for (int i = 0; i < counts.size(); i++) {
        if (counts[i] > 500) {
            gamma[i] = 1;
        } else {
            epsilon[i] = 1;
        }
    }

    int gamma_int = 0;
    int epsilon_int = 0;
    int index_counter = 0;

    for (int i = gamma.size()-1; i>=0; i--) {
        if (gamma[i]) {
            gamma_int += pow(2, index_counter);
        }

        if (epsilon[i]) {
            epsilon_int += pow(2, index_counter);
        }

        index_counter++;
    }


    // output the results
    cout << "Part 1: " << gamma_int*epsilon_int << endl;

    vector<string> lines_o2 = lines;
    vector<string> lines_co2 = lines;

    int index = 0;
    while (lines_o2.size() > 1) {
        int ones = 0;
        for (const string& line : lines_o2) {
            ones += stoi(line.substr(index, 1));
        }

        int zeros = lines_o2.size() - ones;
        char to_remove;

        if (ones >= zeros) {
            to_remove = '0';
        } else {
            to_remove = '1';
        }

        lines_o2.erase(remove_if(lines_o2.begin(), lines_o2.end(),
           [index, to_remove](const string& str) {
               return (to_remove == str[index]);
           }), lines_o2.end());

        index++;
    }

    index = 0;
    while (lines_co2.size() > 1) {
        int ones = 0;
        for (const string& line : lines_co2) {
            ones += stoi(line.substr(index, 1));
        }

        int zeros = lines_co2.size() - ones;
        char to_remove;

        if (ones >= zeros) {
            to_remove = '1';
        } else {
            to_remove = '0';
        }

        lines_co2.erase(remove_if(lines_co2.begin(), lines_co2.end(),
           [index, to_remove](const string& str) {
               return (to_remove == str[index]);
           }), lines_co2.end());

        index++;
    }

    int o2_int = 0;
    int co2_int = 0;
    index_counter = 0;

    for (int i=11; i>=0; i--) {
        if (lines_co2[0][i] == '1') {
            co2_int += pow(2, index_counter);
        }

        if (lines_o2[0][i] == '1') {
            o2_int += pow(2, index_counter);
        }

        index_counter++;
    }

    // output the results
    cout << "Part 2: " << o2_int*co2_int << endl;
}