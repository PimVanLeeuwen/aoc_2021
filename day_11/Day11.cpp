//
// Created by pimvanleeuwen on 11/12/24.
//

#include "Day11.h"

#include <algorithm>
#include <iostream>
#include <ostream>

using namespace std;

// Octopus for our grid
class Octopus {
public:
    int power;
    int x; int y;
    bool queued = false;
    bool flashed = false;

    explicit Octopus(int p, const int x, const int y) : power(p), x(x), y(y) {}
};

void Day11::execute(const vector<string> &lines) {
    vector<vector<Octopus>> grid;
    constexpr int STEPS = 900;
    long part_1 = 0;

    // make our grid of octopus
    for (int y = 0; y < lines.size(); ++y) {
        // create a line
        vector<Octopus> grid_line; grid_line.reserve(lines.size());
        for (int x = 0; x < lines.size(); ++x) {
            grid_line.emplace_back(lines[y][x]-'0', x, y);
        }
        grid.emplace_back(grid_line);
    }

    // each iteration of this loop will be a step
    for (int i = 0; i < STEPS; i++) {
        vector<pair<int, int>> to_flash;

        // first is increasing the energy level of each octopus
        for (auto &grid_line : grid) {
            for (auto &octopus : grid_line) {
                octopus.power++;
                // if it becomes greater than 9 it will be added to the flash queue

                if (octopus.power > 9) {
                    octopus.queued = true;
                    to_flash.emplace_back(octopus.x, octopus.y);
                }
            }
        }

        // Then we flash all the octopus until none are left
        while (!to_flash.empty()) {
            auto coords = to_flash.back();
            to_flash.pop_back();
            grid[coords.second][coords.first].flashed = true;
            part_1++;

            // increase power of neighbours and add them if they where not present before
            for (int x = coords.first - 1; x <= coords.first + 1; ++x) {
                for (int y = coords.second - 1; y <= coords.second + 1; ++y) {
                    // no out of bounds please
                    if (x < 0 || x >= grid.size() || y < 0 || y >= grid.size()) {
                        continue;
                    }
                    grid[y][x].power++;
                    if (grid[y][x].power > 9 && !grid[y][x].flashed && !grid[y][x].queued) {
                        grid[y][x].queued = true;
                        to_flash.emplace_back(x,y);
                    }
                }
            }
        }

        int count = 0;
        // reset all octopus that have flashed
        for (auto &grid_line : grid) {
            for (auto &octopus : grid_line) {
                if (octopus.flashed) {
                    count++;
                    octopus.power = 0;
                    octopus.flashed = false;
                    octopus.queued = false;
                }
            }
        }

        // break if all flash simultaneous for part 2
        if (count == 100) {
            cout << "Part 2: " << i + 1 << endl;
            break;
        }

        // output part 1 after 100 steps
        if (i == 99) {
            cout << "Part 1: " << part_1 << endl;
        }

    }


}
