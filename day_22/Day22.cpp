//
// Created by pimvanleeuwen on 11/25/24.
//

#include "Day22.h"

#include <iostream>
#include <map>
#include <sstream>

using namespace std;

struct Instruction {
    bool on{};
    pair<int, int> x_range;
    pair<int, int> y_range;
    pair<int, int> z_range;
};

struct Cuboid {
    pair<int, int> x_range;
    pair<int, int> y_range;
    pair<int, int> z_range;
};

// check if two cubes overlap
bool overlap_cuboids(const Cuboid& c1, const Cuboid& c2) {
    return  (c1.x_range.first <= c2.x_range.second && c1.x_range.second >= c2.x_range.first) &&
        (c1.y_range.first <= c2.y_range.second && c1.y_range.second >= c2.y_range.first) &&
        (c1.z_range.first <= c2.z_range.second && c1.z_range.second >= c2.z_range.first);
}

// give the intersection of two cubes
Cuboid intersect(const Cuboid& c1, const Cuboid& c2) {
    return { {max(c1.x_range.first, c2.x_range.first),min(c1.x_range.second, c2.x_range.second)},
        {max(c1.y_range.first, c2.y_range.first), min(c1.y_range.second, c2.y_range.second)},
        {max(c1.z_range.first, c2.z_range.first), min(c1.z_range.second, c2.z_range.second)}};
}

// subtract c2 from c1
vector<Cuboid> subtract(const Cuboid& c1, const Cuboid& c2) {
    vector<Cuboid> result;

    // if they do not overlap we do not have to do anything
    if (!overlap_cuboids(c1, c2)) {
        return {c1};
    }

    // this is the intersection
    Cuboid intersection = intersect(c1, c2);

    // these might still overlap so need to be checked
    if (c1.x_range.first < intersection.x_range.first) {
        Cuboid new_c = {{c1.x_range.first, intersection.x_range.first - 1}, c1.y_range, c1.z_range};
        result.push_back(new_c);
    }
    if (c1.x_range.second > intersection.x_range.second) {
        Cuboid new_c = {{intersection.x_range.second + 1, c1.x_range.second}, c1.y_range, c1.z_range};
        result.push_back(new_c);
    }
    if (c1.y_range.first < intersection.y_range.first) {
        Cuboid new_c = {c1.x_range, {c1.y_range.first, intersection.y_range.first - 1}, c1.z_range};
        result.push_back(new_c);
    }
    if (c1.y_range.second > intersection.y_range.second) {
        Cuboid new_c = {c1.x_range, {intersection.y_range.second + 1, c1.y_range.second}, c1.z_range};
        result.push_back(new_c);
    }
    if (c1.z_range.first < intersection.z_range.first) {
        Cuboid new_c = {c1.x_range, c1.y_range, {c1.z_range.first, intersection.z_range.first - 1}};
        result.push_back(new_c);
    }
    if (c1.z_range.second > intersection.z_range.second) {
        Cuboid new_c = {c1.x_range, c1.y_range, {intersection.z_range.second + 1, c1.z_range.second}};
        result.push_back({c1.x_range, c1.y_range, {intersection.z_range.second + 1, c1.z_range.second}});
    }
}

void Day22::execute(const vector<string> &lines) {
    map<pair<int, int>, bool> grid;

    vector<Cuboid> cuboids;

    for (const auto &line : lines) {
        Instruction instruction;
        istringstream iss(line);
        string part;
        char ign;

        // process the input into an instruction
        iss >> part;
        instruction.on = (part == "on");
        iss >> ign >> ign >> instruction.x_range.first >> ign >> ign >> instruction.x_range.second >> ign;
        iss >> ign >> ign >> instruction.y_range.first >> ign >> ign >> instruction.y_range.second >> ign;
        iss >> ign >> ign >> instruction.z_range.first >> ign >> ign >> instruction.z_range.second >> ign;

        // for now we skip these, is for part 2
        if (instruction.x_range.first > 50 || instruction.x_range.first < 50) {
            continue;
        }



    }

}