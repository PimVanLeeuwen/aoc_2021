//
// Created by pimvanleeuwen on 11/21/24.
//

#include "Day19.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <sstream>

using namespace std;

class Scanner {
    public:
    int number;
    vector<int> coordinates {};
    vector<vector<int>> beacons;
    vector<int> sq_distances_unordered;
    map<pair<int, int>, int> sq_distances{};


    explicit Scanner(const int _number, const vector<vector<int>> &_beacons) : number(_number), beacons(_beacons) {
        for (int i = 0; i < beacons.size(); i++) {
            for (int j = i; j < beacons.size(); j++) {
                int distance = pow((beacons[i][0] - beacons[j][0]),2) +
                    pow(abs(beacons[i][1] - beacons[j][1]),2) +  pow(abs(beacons[i][2] - beacons[j][2]),2);
                sq_distances[make_pair(i, j)] = distance;
                sq_distances_unordered.push_back(distance);
            }
        }

        if (number == 0) {
            coordinates = {0,0,0};
        }
    }
};

bool overlap(Scanner &left, Scanner &right) {
    const set<int> left_set(left.sq_distances_unordered.begin(), left.sq_distances_unordered.end());
    const set<int> right_set(right.sq_distances_unordered.begin(), right.sq_distances_unordered.end());

    int count = 0;

    for (auto &l : left_set) {
        for (auto &r : right_set) {
            if (l == r) {
                count++;
            }
        }
    }

    return count >= 66;
}

vector<int> find_orientation(Scanner &left, Scanner &right) {
    // assumed about the input that the left one is mapped (aka has coordinates) and the right one is not
    // goal is to find two points which are relative

    for (auto& p1_left : left.coordinates) {
        for (auto& p2_left : left.coordinates) {
            for (auto& p1_right : right.coordinates) {
                for (auto& p2_right : right.coordinates) {
                    // it should be that: left coordinates -> p1 (using p1_left) -> right coordinates (using p1_right)
                    // is equal to left coordinates -> p2 (using p2_left) -> right coordinates (using p2_right)
                }
            }
        }
    }


    vector<vector<int>> xyz = right.beacons;

}

void Day19::execute(const vector<string> &lines) {
    vector<vector<int>> beacons;
    int number = 0;
    vector<Scanner> scanners;

    // process the input into the beacons
    for (const auto &line : lines) {
        if (line.empty()) {
            scanners.emplace_back(number, beacons);
            number++;
            beacons.clear();
        } else if (line[1] != '-') {
            stringstream ss(line);
            string token;

            vector<int> beacon;

            while(getline(ss, token, ',')) {
                beacon.push_back(stoi(token));
            }
            beacons.push_back(beacon);
        }
    }

    cout << overlap(scanners[0], scanners[2]) << endl;


}