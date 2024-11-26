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
    pair<long, long> x_range;
    pair<long, long> y_range;
    pair<long, long> z_range;
};

struct Cuboid {
    pair<long, long> x_range;
    pair<long, long> y_range;
    pair<long, long> z_range;
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
vector<Cuboid> subtract(Cuboid& c1, const Cuboid& c2) {
    vector<Cuboid> result;

    // if they do not overlap we do not have to do anything
    if (!overlap_cuboids(c1, c2)) return {c1};

    // this is the intersection
    auto [intersection_x_range, intersection_y_range, intersection_z_range] = intersect(c1, c2);

    // these might still overlap so need to be checked
    if (c1.x_range.first < intersection_x_range.first) {
        result.push_back({{c1.x_range.first, intersection_x_range.first - 1},
            c1.y_range, c1.z_range});
        // shrink the cube, since this part is already added to the results
        c1.x_range.first = intersection_x_range.first;
    }
    if (c1.x_range.second > intersection_x_range.second) {
        result.push_back({{intersection_x_range.second + 1, c1.x_range.second},
            c1.y_range, c1.z_range});
        // shrink the cube, since this part is already added to the results
        c1.x_range.second = intersection_x_range.second;
    }
    if (c1.y_range.first < intersection_y_range.first) {
        result.push_back({c1.x_range,
            {c1.y_range.first, intersection_y_range.first - 1}, c1.z_range});
        // shrink the cube, since this part is already added to the results
        c1.y_range.first = intersection_y_range.first;
    }
    if (c1.y_range.second > intersection_y_range.second) {
        result.push_back({c1.x_range,
            {intersection_y_range.second + 1, c1.y_range.second}, c1.z_range});
        // shrink the cube, since this part is already added to the results
        c1.y_range.second = intersection_y_range.second;
    }
    if (c1.z_range.first < intersection_z_range.first) {
        result.push_back({c1.x_range, c1.y_range,
            {c1.z_range.first, intersection_z_range.first - 1}});
        // shrink the cube, since this part is already added to the results
        c1.z_range.first = intersection_z_range.first;
    }
    if (c1.z_range.second > intersection_z_range.second) {
        result.push_back({c1.x_range, c1.y_range,
            {intersection_z_range.second + 1, c1.z_range.second}});
        // shrink the cube, since this part is already added to the results
        c1.z_range.second = intersection_z_range.second;
    }

    return result;
}

void print_cube(const Cuboid& c1) {
    cout << "Cube: " << endl;
    cout << "X_range: [" << c1.x_range.first << " ; " << c1.x_range.second << "]" << endl;
    cout << "Y_range: [" << c1.y_range.first << " ; " << c1.y_range.second << "]" << endl;
    cout << "Z_range: [" << c1.z_range.first << " ; " << c1.z_range.second << "]" << endl;
}

// number of points in a cube
long count_points(const Cuboid& c1) {
    long x_side = (c1.x_range.second == c1.x_range.first) ? 1 :
        (c1.x_range.second < 0 && c1.x_range.first < 0) ? abs(c1.x_range.first) - abs(c1.x_range.second) + 1 :
        (c1.x_range.second >= 0 && c1.x_range.first >= 0) ? c1.x_range.second - c1.x_range.first + 1:
        (c1.x_range.second + abs(c1.x_range.first) + 1);
    long y_side = (c1.y_range.second == c1.y_range.first) ? 1 :
        (c1.y_range.second < 0 && c1.y_range.first < 0) ? abs(c1.y_range.first) - abs(c1.y_range.second) + 1 :
        (c1.y_range.second >= 0 && c1.y_range.first >= 0) ? c1.y_range.second - c1.y_range.first + 1:
        (c1.y_range.second + abs(c1.y_range.first) + 1);
    long z_side = (c1.z_range.second == c1.z_range.first) ? 1 :
        (c1.z_range.second < 0 && c1.z_range.first < 0) ? abs(c1.z_range.first) - abs(c1.z_range.second) + 1 :
        (c1.z_range.second >= 0 && c1.z_range.first >= 0) ? c1.z_range.second - c1.z_range.first + 1:
        (c1.z_range.second + abs(c1.z_range.first) + 1);

    return x_side*y_side*z_side;
}

void process_cubes(const vector<string> &lines, bool part_1) {
    // list of on cubes
    vector<Cuboid> cuboids_on;

    // process each of the lines
    for (const auto &line : lines) {
        Cuboid to_process;
        istringstream iss(line);
        string part;
        char ign;

        // process the input into an instruction
        iss >> part;
        bool on = (part == "on");
        iss >> ign >> ign >> to_process.x_range.first >> ign >> ign >> to_process.x_range.second >> ign;
        iss >> ign >> ign >> to_process.y_range.first >> ign >> ign >> to_process.y_range.second >> ign;
        iss >> ign >> ign >> to_process.z_range.first >> ign >> ign >> to_process.z_range.second >> ign;

        // for part 1 we do not process these
        if ((to_process.x_range.first > 50 || to_process.x_range.first < -50) && part_1) continue;

        // new list of cubes
        vector<Cuboid> cuboids_on_new;

        // first subtract this from every other cube to prevent duplicates
        for (auto &c : cuboids_on) {
            vector<Cuboid> cuboids_on_new_temp = subtract(c, to_process);
            cuboids_on_new.insert( cuboids_on_new.end(),
                cuboids_on_new_temp.begin(), cuboids_on_new_temp.end() );
        }

        // if the cube is on, we add it again
        if (on) cuboids_on_new.push_back(to_process);

        cuboids_on = cuboids_on_new;
    }

    long output = 0;
    for (auto &cuboid : cuboids_on) output += count_points(cuboid);
    (part_1) ? cout << "Part 1: " << output << endl : cout << "Part 2: " << output << endl;
}

void Day22::execute(const vector<string> &lines) {
    process_cubes(lines, true);
    process_cubes(lines, false);
}