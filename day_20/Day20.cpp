//
// Created by pimvanleeuwen on 11/22/24.
//

#include "Day20.h"

#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

void Day20::execute(const vector<string> &lines) {
    constexpr int STEPS = 50;

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

    // perform a step
    for (int s = 0; s < STEPS; s++) {
        // for part 1 we stop earlier
        if (s == 2) {
            int part_1 = 0;
            for (auto &row : image) { part_1 += count(row.begin(), row.end(), true); }
            cout << "Part 1: " << part_1 << endl;
        }
        vector<vector<bool>> new_image = image;
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

                // place the new image part
                new_image[y][x] = lens[index];

                // also fix the edges if we are near them
                if (x == 1) { new_image[y][0] = lens[index]; }
                if (x == image.size()-2) { new_image[y][image.size()-1] = lens[index]; }
                if (y == 1) { new_image[0][x] = lens[index]; }
                if (y == image.size()-2) { new_image[image.size()-1][x] = lens[index]; }
            }
        }

        // final corners
        new_image[0][0] = new_image[0][1];
        new_image[image.size()-1][0] = new_image[image.size()-1][1];
        new_image[0][image.size()-1] = new_image[1][image.size()-1];
        new_image[image.size()-1][image.size()-1] = new_image[image.size()-1][image.size()-2];

        image = new_image;
    }

    // count everything for part 2
    int part_2 = 0;
    for (auto &row : image) { part_2 += count(row.begin(), row.end(), true); }
    cout << "Part 2: " << part_2 << endl;
}
