//
// Created by pimvanleeuwen on 11/15/24.
//

#include "Day15.h"

#include <deque>
#include <iostream>
#include <limits.h>
#include <ostream>
#include <queue>
#include <set>

using namespace std;

struct Compare {
    bool operator()(const pair<int, pair<int, int>>& a, const pair<int, pair<int, int>>& b) const {
        return a.first > b.first;
    }
};

void dijkstra(priority_queue<pair<int, pair<int,int>>, vector<pair<int, pair<int, int>>>,
    Compare>& unv, vector<vector<pair<int, int>>>& rg) {

    // possible neighbours
    vector<pair<int, int>> TRANSPOSITIONS = {{0,-1}, {0,1}, {1,0}, {-1,0}};
    set<pair<int, int>> visited;

    // Dijkstra's
    while (!unv.empty()) {
        auto [x_c, y_c] = unv.top().second; unv.pop();

        // skip if already visited
        if (visited.find({x_c, y_c}) != visited.end()) continue;
        visited.emplace(x_c, y_c);

        // check all unvisited neighbours
        for (const auto &[x_t, y_t] : TRANSPOSITIONS) {
            const int x_new = x_c + x_t;
            const int y_new = y_c + y_t;

            if (x_new >= 0 && x_new < rg.size() &&
                y_new >= 0 && y_new < rg.size() &&
                visited.find({x_new, y_new}) == visited.end()) {

                // update length if needed
                if (rg[y_new][x_new].second > rg[y_c][x_c].second + rg[y_new][x_new].first) {
                    rg[y_new][x_new].second = rg[y_c][x_c].second + rg[y_new][x_new].first;

                    unv.push({rg[y_new][x_new].second,{x_new, y_new}});
                }
            }
        }
    }
}

void Day15::execute(const vector<string> &lines) {
    // alternative solution for part 2 would indeed be considering that the shortest path in each of the grids will
    // be the same so that you can compute the total distance based on the result from part 1.

    // normal grid and exploded one
    vector<vector<pair<int, int>>> risk_grid;
    vector risk_grid_2(500, vector<pair<int, int>>(500, {0, INT_MAX}));

    // set of unvisited nodes
    set<pair<int, int>> unvisited;
    set<pair<int, int>> unvisited_2;

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, Compare> pq;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, Compare> pq_2;

    // process the input
    for (const auto &line : lines) {
        vector<pair<int, int>> row;
        for (const auto &c : line) {
            row.emplace_back(c - '0', INT_MAX);
        }
        risk_grid.push_back(row);
    }

    // create the grid of part 2
    for (int y = 0; y < risk_grid_2.size(); y++) {
        for (int x = 0; x < risk_grid_2[y].size(); x++) {
            const int t_row = x/100;
            const int t_col = y/100;
            auto [risk_og, distance_og] = risk_grid[y%100][x%100];
            const pair<int, int> new_val = {(((risk_og + t_row + t_col) - 1) % 9) + 1, INT_MAX};
            risk_grid_2[y][x] = new_val;
        }
    }

    // set the starting distances
    risk_grid[0][0].second = 0;
    risk_grid_2[0][0].second = 0;

    // initially we still need to visit all the nodes
    for (int x = 0; x < 500; x++) {
        for (int y = 0; y < 500; y++) {
            if (y < 100 && x < 100) {
                pq.push({risk_grid[y][x].second, {x,y}});
            }
            pq_2.push({risk_grid_2[y][x].second, {x,y}});
        }
    }

    // Dijkstra on the small one
    dijkstra(pq, risk_grid);
    cout << "Part 1: " << risk_grid[99][99].second << endl;

    // Dijkstra on the big one
    dijkstra(pq_2, risk_grid_2);
    cout << "Part 2: " << risk_grid_2[499][499].second << endl;

}
