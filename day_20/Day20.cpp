//
// Created by pimvanleeuwen on 11/22/24.
//

#include "Day20.h"

#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

void Day20::execute(const vector<string> &lines) {
    constexpr int STEPS_PART_1 = 2;

    // false = .
    // true = #
    vector<bool> lens;
    lens.reserve(512); // allocate the rows already
    vector<vector<bool>> image;
    image.reserve(300); // allocate the rows already

    // place 100 rows empty above
    for (int i = 0; i < 100; i++) { image.emplace_back(300, false); }

    for (const auto &line : lines) {

        // this is for the empty and start lines
        if (line.length() != 100) {
            for (const auto &c : line) {
                lens.push_back(c == '#');
            }
            continue;
        }

        // add 100 elements of padding to the grid, which should be "infinite" enough
        auto row = vector(100, false);
        auto row_end = vector(100, false);
        for (const auto &c : line) {
            row.push_back(c == '#');
        }
        row.insert(row.end(), row_end.begin(), row_end.end());
        image.push_back(row);
    }

    // place 100 rows empty below the image
    for (int i = 0; i < 100; i++) { image.emplace_back(300, false); }

    for (auto &row : image) {
        for (auto c : row) {
            if (c) {
                cout << "#";
            } else {
                cout << ".";
            }
        }
        cout << endl;
    }

    cout << endl;
    cout << endl;


    // perform a step
    for (int s = 0; s < STEPS_PART_1; s++) {
        for (int x = 1; x < image.size()-1; x++) {
            for (int y = 1; y < image.size()-1; y++) {
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

                image[y][x] = lens[index];
            }
        }

        for (auto &row : image) {
            for (auto c : row) {
                if (c) {
                    cout << "#";
                } else {
                    cout << ".";
                }
            }
            cout << endl;
        }

        cout << endl;
        cout << endl;
    }

    int part_1 = 0;

    for (auto &row : image) {
        part_1 += count(row.begin(), row.end(), true);
    }

    cout << "Part 1: " << part_1 << endl;
}
