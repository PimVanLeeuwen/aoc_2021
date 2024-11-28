//
// Created by pimvanleeuwen on 11/26/24.
//

#include "Day23.h"

#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <ostream>

using namespace std;

const map<pair<int, int>, char> DESTINATIONS = {{{3,2},'A'}, {{3,3},'A'}, {{3,4},'A'}, {{3,5},'A'},
    {{5,2},'B'}, {{5,3},'B'}, {{5,4},'B'}, {{5,5},'B'}, {{7,2},'C'},
    {{7,3},'C'}, {{7,4},'C'}, {{7,5},'C'}, {{9,2},'D'}, {{9,3},'D'},
    {{9,4},'D'}, {{9,5},'D'}};
map<vector<vector<char>>, int> KNOWN_BRANCHES = {};
const vector<pair<int,int>> HALL_POSITIONS = {{1,1}, {2,1}, {4,1}, {6,1}, {8,1},
    {10,1},{11,1}};
const vector<pair<int,int>> ROOM_POSITIONS = {{3,2}, {3,3}, {5,2}, {5, 3},
    {7,2}, {7,3}, {9,2}, {9,3}};
const vector<pair<int,int>> ROOM_POSITIONS_2 = {{3,2}, {3,3}, {3,4}, {3,5}, {5,2}, {5, 3}, {5,4}, {5,5},
    {7,2}, {7,3}, {7,4}, {7,5}, {9,2}, {9,3}, {9,4}, {9,5}};
const vector<pair<int,int>> ALL_POSITIONS = {{1,1}, {2,1}, {4,1}, {6,1}, {8,1},
    {10,1},{11,1}, {3,2}, {3,3}, {5,2}, {5, 3},
    {7,2}, {7,3}, {9,2}, {9,3}};

bool free_path(const vector<vector<char>> &map, const pair<int, int> &origin, const pair<int, int> &dest) {
    // Move until we are at the location or we reach a point where we cannot move any more.
    int x = origin.first;
    int y = origin.second;

    while (x != dest.first || y != dest.second) {
        if (x < dest.first && map[y][x+1] == '.') { x++; }
        else if (x > dest.first && map[y][x-1] == '.') { x--; }
        else if (y > dest.second && map[y-1][x] == '.') { y--; }
        else if (y < dest.second && map[y+1][x] == '.') { y++; }
        else { return false; }
    }

    return true;
}

bool can_move(vector<vector<char>> &map, const pair<int, int> &pos) {
    // in this case we are already at the destination location and we will not move any more
    if (find(ROOM_POSITIONS.begin(), ROOM_POSITIONS.end(), pos) != ROOM_POSITIONS.end()) {
        if (DESTINATIONS.at(pos) == map[pos.second][pos.first] &&
            (pos.second == 3 || map[3][pos.first] == DESTINATIONS.at({pos.first, 3}))) {
                return false;
        }
    }


    // if we are on the hallway, here every snail can only possibly move to one of the two locations in their respective
    // rooms, for convenience we only allow to move from back to the front.
    if (pos.second == 1) {
        switch (map[pos.second][pos.first]) {
            case 'A': return (free_path(map, pos, {3,2}) && map[3][3] == 'A') ||
                free_path(map, pos, {3,3});
            case 'B': return (free_path(map, pos, {5,2}) && map[3][5] == 'B') ||
                free_path(map, pos, {5,3});
            case 'C': return (free_path(map, pos, {7,2}) && map[3][7] == 'C') ||
                free_path(map, pos, {7,3});
            case 'D': return (free_path(map, pos, {9,2}) && map[3][9] == 'D') ||
                free_path(map, pos, {9,3});
            default:
                return false;
        }
    } else {
        // we are in a room, but not yet where we need to be, can only move to a hall position
        return any_of(HALL_POSITIONS.begin(), HALL_POSITIONS.end(),
            [map, pos](const pair<int, int> &dest) { return free_path(map, pos, dest); });
    }
}

bool can_move_2(vector<vector<char>> &map, const pair<int, int> &pos) {
    // in this case we are already at the destination location and we will not move any more
    if (find(ROOM_POSITIONS_2.begin(), ROOM_POSITIONS_2.end(), pos) != ROOM_POSITIONS_2.end()) {
        if (DESTINATIONS.at(pos) == map[pos.second][pos.first] &&
            (pos.second == 2 && (map[3][pos.first] == DESTINATIONS.at({pos.first, 3}) && map[4][pos.first] == DESTINATIONS.at({pos.first, 4}) && map[5][pos.first] == DESTINATIONS.at({pos.first, 5})))
            ||  (pos.second == 3 && map[4][pos.first] == DESTINATIONS.at({pos.first, 4}) && map[5][pos.first] == DESTINATIONS.at({pos.first, 5}))
            ||  (pos.second == 4 && map[5][pos.first] == DESTINATIONS.at({pos.first, 5}))
            ||  pos.second == 5) {
                return false;
            }
    }


    // if we are on the hallway, here every snail can only possibly move to one of the two locations in their respective
    // rooms, for convenience we only allow to move from back to the front.
    if (pos.second == 1) {
        switch (map[pos.second][pos.first]) {
            case 'A':
                return (free_path(map, pos, {3,2}) && map[3][3] == 'A' && map[4][3] == 'A' && map[5][3] == 'A'
                    || free_path(map, pos, {3,3}) && map[4][3] == 'A' && map[5][3] == 'A'
                    || free_path(map, pos, {3,4}) && map[5][3] == 'A'
                    || free_path(map, pos, {3,5}));
            case 'B':
                return (free_path(map, pos, {5,2}) && map[3][5] == 'B' && map[4][5] == 'B' && map[5][5] == 'B'
                    || free_path(map, pos, {5,3}) && map[4][5] == 'B' && map[5][5] == 'B'
                    || free_path(map, pos, {5,4}) && map[5][5] == 'B'
                    || free_path(map, pos, {5,5}));
            case 'C':
                return (free_path(map, pos, {7,2}) && map[3][7] == 'C' && map[4][7] == 'C' && map[5][7] == 'C'
                    || free_path(map, pos, {7,3}) && map[4][7] == 'C' && map[5][7] == 'C'
                    || free_path(map, pos, {7,4}) && map[5][7] == 'C'
                    || free_path(map, pos, {7,5}));
            case 'D':
                return (free_path(map, pos, {9,2}) && map[3][9] == 'D' && map[4][9] == 'D' && map[5][9] == 'D'
                    || free_path(map, pos, {9,3}) && map[4][9] == 'D' && map[5][9] == 'D'
                    || free_path(map, pos, {9,4}) && map[5][9] == 'D'
                    || free_path(map, pos, {9,5}));
            default:
                return false;
        }
    } else {
        // we are in a room, but not yet where we need to be, can only move to a hall position
        return any_of(HALL_POSITIONS.begin(), HALL_POSITIONS.end(),
            [map, pos](const pair<int, int> &dest) { return free_path(map, pos, dest); });
    }
}

vector<pair<int, int>> give_moves(vector<vector<char>> &map, const pair<int, int> &pos) {
    // if it cannot move return the empty set
    if (!can_move(map, pos) || map[pos.second][pos.first] == '.') {
        return {};
    }

    vector<pair<int, int>> moves;

    // we move into a room
    if (pos.second == 1) {
        switch (map[pos.second][pos.first]) {
            case 'A':
                if (free_path(map, pos, {3,2}) && map[3][3] == 'A') { moves.emplace_back(3,2); }
                else if (free_path(map, pos, {3,3})) { moves.emplace_back(3,3); }
                break;
            case 'B':
                if (free_path(map, pos, {5,2}) && map[3][5] == 'B') { moves.emplace_back(5,2); }
                else if (free_path(map, pos, {5,3})) { moves.emplace_back(5,3); }
                break;
            case 'C':
                if (free_path(map, pos, {7,2}) && map[3][7] == 'C') { moves.emplace_back(7,2); }
                else if (free_path(map, pos, {7,3})) { moves.emplace_back(7,3); }
                break;
            case 'D':
                if (free_path(map, pos, {9,2}) && map[3][9] == 'D') { moves.emplace_back(9,2); }
                else if (free_path(map, pos, {9,3})) { moves.emplace_back(9,3); }
                break;
            default:
                return {};
        }
    } else {
        // here we move into the hall
        for (auto &possible_dest : HALL_POSITIONS) {
            if (free_path(map, pos, possible_dest)) { moves.emplace_back(possible_dest); }
        }
    }

    return moves;
}

vector<pair<int, int>> give_moves_2(vector<vector<char>> &map, const pair<int, int> &pos) {
    // if it cannot move return the empty set
    if (!can_move(map, pos) || map[pos.second][pos.first] == '.') {
        return {};
    }

    vector<pair<int, int>> moves;

    // we move into a room
    if (pos.second == 1) {
        switch (map[pos.second][pos.first]) {
            case 'A':
                if (free_path(map, pos, {3,2}) && map[3][3] == 'A' && map[4][3] == 'A' && map[5][3] == 'A') { moves.emplace_back(3,2); }
                else if (free_path(map, pos, {3,3}) && map[4][3] == 'A' && map[5][3] == 'A') { moves.emplace_back(3,3); }
                else if (free_path(map, pos, {3,4}) && map[5][3] == 'A') { moves.emplace_back(3,4); }
                else if (free_path(map, pos, {3,5})) { moves.emplace_back(3,5); }
                break;
            case 'B':
                if (free_path(map, pos, {5,2}) && map[3][5] == 'B' && map[4][5] == 'B' && map[5][5] == 'B') { moves.emplace_back(5,2); }
                else if (free_path(map, pos, {5,3}) && map[4][5] == 'B' && map[5][5] == 'B') { moves.emplace_back(5,3); }
                else if (free_path(map, pos, {5,4}) && map[5][5] == 'B') { moves.emplace_back(5,4); }
                else if (free_path(map, pos, {5,5})) { moves.emplace_back(5,5); }
            break;
            case 'C':
                if (free_path(map, pos, {7,2}) && map[3][7] == 'C' && map[4][7] == 'C' && map[5][7] == 'C') { moves.emplace_back(7,2); }
                else if (free_path(map, pos, {7,3}) && map[4][7] == 'C' && map[5][7] == 'C') { moves.emplace_back(7,3); }
                else if (free_path(map, pos, {7,4}) && map[5][7] == 'C') { moves.emplace_back(7,4); }
                else if (free_path(map, pos, {7,5})) { moves.emplace_back(7,5); }
            break;
            case 'D':
                if (free_path(map, pos, {9,2}) && map[3][9] == 'D' && map[4][9] == 'D' && map[5][9] == 'D') { moves.emplace_back(9,2); }
                else if (free_path(map, pos, {9,3}) && map[4][9] == 'D' && map[5][9] == 'D') { moves.emplace_back(9,3); }
                else if (free_path(map, pos, {9,4}) && map[5][9] == 'D') { moves.emplace_back(9,4); }
                else if (free_path(map, pos, {9,5})) { moves.emplace_back(9,5); }
            break;
            default:
                return {};
        }
    } else {
        // here we move into the hall
        for (auto &possible_dest : HALL_POSITIONS) {
            if (free_path(map, pos, possible_dest)) { moves.emplace_back(possible_dest); }
        }
    }

    return moves;
}

int do_move(vector<vector<char>> &map, const pair<int, int> &source, const pair<int, int> &des) {
    if (!free_path(map, source, des)) { throw runtime_error("Doing invalid move"); }
    int multiplier;

    // compute cost per step
    switch (map[source.second][source.first]) {
        case 'A': multiplier = 1; break;
        case 'B': multiplier = 10; break;
        case 'C': multiplier = 100; break;
        case 'D': multiplier = 1000; break;
        default : throw runtime_error("Doing invalid move char");
    }

    // switch destination and source (source is always a free space here)
    map[des.second][des.first] = map[source.second][source.first];
    map[source.second][source.first] = '.';

    // for (const auto &line : map) {
    //     for (const auto &c : line) { cout << c; }
    //     cout << endl;
    // }
    // cout << endl;

    // compute cost
    return (abs(des.first - source.first) + abs(des.second - source.second)) * multiplier;
}

bool is_valid (const vector<vector<char>> &map) {
    return map[2][3] == 'A' && map[3][3] == 'A' &&
        map[2][5] == 'B' && map[3][5] == 'B' &&
        map[2][7] == 'C' && map[3][7] == 'C' &&
        map[2][9] == 'D' && map[3][9] == 'D';
}

long solve_part_1(vector<vector<char>> &map, bool first) {

    vector<pair<pair<int, int>, pair<int, int>>> possible_moves;

    if (KNOWN_BRANCHES.find(map) != KNOWN_BRANCHES.end()) {
        return KNOWN_BRANCHES.at(map);
    }

    // gather all possible moves that we can do here
    for (const auto &s : ALL_POSITIONS) {
        vector<pair<int, int>> destinations = give_moves(map, s);
        for (const auto &d : destinations) {possible_moves.emplace_back(s, d);}
    }

    // in this case the puzzle is done
    if (is_valid(map)) {
        return 0;
    }
    if (possible_moves.empty()) {
        return -1;
    }

    if (first) {
        cout << possible_moves.size() << endl;
    }
    int i = 0;

    long min_cost = INT_MAX;
    for (const auto [source, dest] : possible_moves) {
        if (first) {
            cout << i++ << endl;
        }
        const long cost_move = do_move(map, source, dest);
        const long cost_new_map = solve_part_1(map, false);
        // disregard invalid solutions
        if (cost_new_map != -1) {
            KNOWN_BRANCHES.insert({map, cost_new_map});
            min_cost = min(min_cost, cost_new_map + cost_move);
        }

        do_move(map, dest, source);

    }

    return min_cost;
}

void Day23::execute(const vector<string> &lines) {
    // ps I know they are not snails, but it writes easier
    // this is the map of the snails
    vector<vector<char>> map;

    for (const string &line : lines) {
        vector<char> char_line;
        for (const char &c : line) { char_line.push_back(c); }
        map.push_back(char_line);
    }

    int part_1 = solve_part_1(map, true);

    cout << "Part 1: " << part_1 << endl;

}
