//
// Created by pimvanleeuwen on 11/30/24.
//

#include "Day25.h"

#include <iostream>
#include <ostream>

using namespace std;

vector<vector<char>> do_move_east(const vector<vector<char>>& map) {
    vector result(map.size(), vector<char>(map[0].size(), '.'));
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '>' && (j < map[0].size()-1 && map[i][j+1] == '.')) { result[i][j+1] = '>'; }
            else if (map[i][j] == '>' && (j == map[0].size()-1 && map[i][0] == '.')) { result[i][0] = '>'; }
            else if (map[i][j] == 'v') { result[i][j] = 'v'; }
            else if (map[i][j] == '>') { result[i][j] = '>'; }
        }
    }
    return result;
}

vector<vector<char>> do_move_south(const vector<vector<char>>& map) {
    vector result(map.size(), vector<char>(map[0].size(), '.'));
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 'v' && (i < map.size()-1 && map[i+1][j] == '.')) { result[i+1][j] = 'v'; }
            else if (map[i][j] == 'v' && (i == map.size()-1 && map[0][j] == '.')) { result[0][j] = 'v'; }
            else if (map[i][j] == 'v') { result[i][j] = 'v'; }
            else if (map[i][j] == '>') { result[i][j] = '>'; }
        }
    }
    return result;
}

bool can_move(const vector<vector<char>>& map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 'v' && ((i < map.size()-1 && map[i+1][j] == '.') || (i == map.size() - 1 && map[0][j] == '.'))) return true;
            if (map[i][j] == '>' && ((j < map[0].size()-1 && map[i][j+1] == '.') || (j == map[0].size() - 1 && map[i][0] == '.'))) return true;
        }
    }
    return false;
}

void Day25::execute(const vector<string> &lines) {
    vector<vector<char>> map;

    // load in the map
    for (const auto &line : lines) {
        vector<char> row;
        for (const auto &c : line) { row.push_back(c); }
        map.push_back(row);
    }


    // while we can still make moves
    int moves_done = 0;
    while (can_move(map)) {
        map = do_move_east(map);
        map = do_move_south(map);
        moves_done++;
        if (moves_done % 1000 == 0) cout << moves_done << endl;
    }

    cout << "Part 1: " << moves_done + 1 << endl;
}