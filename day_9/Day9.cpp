//
// Created by pimvanleeuwen on 11/12/24.
//

#include "Day9.h"

#include <algorithm>
#include <deque>
#include <iostream>
#include <ostream>
#include <set>
#include <utility>

using namespace std;

// check if a coordinate is included by its neighbours and if so compute the risk
int compute_risk(const vector<vector<int>>& height_map, const int x, const int y) {
    if (height_map[x][y] < height_map[x - 1][y] &&
        height_map[x][y] < height_map[x + 1][y] &&
        height_map[x][y] < height_map[x][y - 1] &&
        height_map[x][y] < height_map[x][y + 1]) {

        return height_map[x][y] + 1;

        }

    return 0;
}

void Day9::execute(const vector<string> &lines) {

    int part_1 = 0;

    vector<vector<int>> height_map;
    // we will add some padding to make computations easier and not deal with out-of-bounds
    height_map.emplace_back(102, 9);

    // add the input to the grid
    for (auto &line : lines) {
         vector<int> row = {9};

        for (auto &c : line) {
            row.push_back(c - '0');
        }

        row.push_back(9);
        height_map.push_back(row);

    }
    height_map.emplace_back(102, 9);

    // possible pairs for neighbors to the right or left
    vector<pair<int, int>> x_y_neighbours = {{-1,0}, {1,0}, {0,1}, {0,-1}};

    // this will be the set of covered points and the set of basin sizes
    set<pair<int, int>> covered;
    vector<size_t> sizes;

    for (int x = 1; x <= 100; x++) {
        for (int y = 1; y <= 100; y++) {
            // do part 1 for each point
            part_1 += compute_risk(height_map, x, y);

            // only cover point we have not yet covered before for part 2
            if (covered.find(pair(x,y)) != covered.end() ||
                height_map[x][y] == 9) {
                continue;
            }

            // for part 2 we will basically just flood the basin by using a queue and breadth first search
            // to process still, contains initial node
            deque<pair<int, int>> q = {{x,y}};
            // visited
            set<pair<int, int>> s;

            // as long as we have elements, continue
            while (!q.empty()) {
                // remove new place from the queue
                auto c = q.front(); q.pop_front();

                // check if we must add its neighbours
                for (auto n : x_y_neighbours) {
                    int x_n = c.first + n.first;
                    int y_n = c.second + n.second;

                    // check if the neighbour is either too high or already in the queue
                    auto deq_pres = find(q.begin(), q.end(), pair(x_n,y_n));
                    auto set_pres = s.find(pair(x_n,y_n));
                    if (height_map[x_n][y_n] != 9 && deq_pres == q.end() && set_pres == s.end()) {
                        q.emplace_back(x_n,y_n);
                    }
                }

                // add to the basin
                s.insert(c);
                // we do not want to visit every point of the same basin, so keep track of that
                covered.insert(c);
            }

            // add the basin to the list of sizes
            sizes.push_back(s.size());
        }
    }

    // sort to get the highest three basins
    sort(sizes.begin(), sizes.end());
    size_t part_2 = sizes[sizes.size()-1] * sizes[sizes.size()-2] * sizes[sizes.size()-3];

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}


