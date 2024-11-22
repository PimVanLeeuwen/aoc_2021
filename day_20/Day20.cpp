//
// Created by pimvanleeuwen on 11/22/24.
//

#include "Day20.h"

#include <cmath>
#include <iostream>

using namespace std;

void Day20::execute(const vector<string> &lines) {

    constexpr int STEPS_PART_1 = 2;

    // false = .
    // true = #
    vector<vector<bool>> image;
    for (const auto &line : lines) {
        // add a 100 elements of padding to the grid, which should be "infinite" enough
        auto row = vector(100, false);
        auto row_end = vector(100, false);
        for (const auto &c : line) {
            row.push_back(c == '#');
        }
        row.insert(row.end(), row_end.begin(), row_end.end());
        image.push_back(row);
    }

    // perform a step
    for (int s = 0; s < STEPS_PART_1; s++) {
        for (int x = 1; x < image.size()-1; x++) {
            for (int y = 1; y < image[x].size()-1; y++) {
                // get the window around
                vector<bool> context_window = {
                    image[y-1][x-1], image[y-1][x], image[y-1][x+1],
                    image[y][x-1], image[y][x], image[y][x+1],
                    image[y+1][x-1], image[y+1][x], image[y+1][x+1],
                };

                // compute the binary number
                int index = 0;
                for (int i = 0; i < context_window.size(); i++) {
                    if (context_window[i]) {
                        index += pow(2, 8-i);
                    }
                }
            }
        }
    }



}