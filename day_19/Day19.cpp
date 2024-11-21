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
    }
};

bool overlap(const Scanner &left, const Scanner &right) {
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

// yes this is hardcoded, we will deal with it
vector<int> permute(const int d, vector<int> v) {
    switch(d) {
        default: return {v[0], v[1], v[2]};
        case 0: return {v[0], v[1], -v[2]};
        case 1: return {v[0], -v[1], v[2]};
        case 2: return {-v[0], v[1], v[2]};
        case 3: return {-v[0], -v[1], v[2]};
        case 4: return {-v[0], -v[1], -v[2]};
        case 5: return {v[0], -v[1], -v[2]};
        case 6: return {-v[0], v[1], -v[2]};

        case 7: return {v[1], v[0], v[2]};
        case 8: return {v[1], v[0], -v[2]};
        case 9: return {v[1], -v[0], v[2]};
        case 10: return {-v[1], v[0], v[2]};
        case 11: return {-v[1], -v[0], v[2]};
        case 12: return {-v[1], -v[0], -v[2]};
        case 13: return {v[1], -v[0], -v[2]};
        case 14: return {-v[1], v[0], -v[2]};

        case 15: return {v[1], v[2], v[0]};
        case 16: return {v[1], v[2], -v[0]};
        case 17: return {v[1], -v[2], v[0]};
        case 18: return {-v[1], v[2], v[0]};
        case 19: return {-v[1], -v[2], v[0]};
        case 20: return {-v[1], -v[2], -v[0]};
        case 21: return {v[1], -v[2], -v[0]};
        case 22: return {-v[1], v[2], -v[0]};

        case 23: return {v[0], v[2], v[1]};
        case 24: return {v[0], v[2], -v[1]};
        case 25: return {v[0], -v[2], v[1]};
        case 26: return {-v[0], v[2], v[1]};
        case 27: return {-v[0], -v[2], v[1]};
        case 28: return {-v[0], -v[2], -v[1]};
        case 29: return {v[0], -v[2], -v[1]};
        case 30: return {-v[0], v[2], -v[1]};

        case 31: return {v[2], v[1], v[0]};
        case 32: return {v[2], v[1], -v[0]};
        case 33: return {v[2], -v[1], v[0]};
        case 34: return {-v[2], v[1], v[0]};
        case 35: return {-v[2], -v[1], v[0]};
        case 36: return {-v[2], -v[1], -v[0]};
        case 37: return {v[2], -v[1], -v[0]};
        case 38: return {-v[2], v[1], -v[0]};

        case 39: return {v[2], v[0], v[1]};
        case 40: return {v[2], v[0], -v[1]};
        case 41: return {v[2], -v[0], v[1]};
        case 42: return {-v[2], v[0], v[1]};
        case 43: return {-v[2], -v[0], v[1]};
        case 44: return {-v[2], -v[0], -v[1]};
        case 45: return {v[2], -v[0], -v[1]};
        case 46: return {-v[2], v[0], -v[1]};
    }
}

void place_scanner(const Scanner &left, Scanner &right) {
    // assumed about the input that the left one is mapped (aka has coordinates) and the right one is not
    // goal is to find two points which are relative

    for (auto& p1_left : left.beacons) {
        for (auto& p2_left : left.beacons) {
            if (p1_left == p2_left) {
                continue;
            }
            for (auto& p1_right : right.beacons) {
                for (auto& p2_right : right.beacons) {
                    if (p1_right == p2_right) {
                        continue;
                    }
                    // it should be that: left coordinates -> s1 (using p1_left) -> right coordinates (using p1_right)
                    // is equal to left coordinates -> s2 (using p2_left) -> right coordinates (using p2_right)
                    for (int d = 0; d < 48; d++) {
                        vector<int> p1_right_permute = permute(d, p1_right);
                        vector<int> p2_right_permute = permute(d, p2_right);
                        vector<int> right_1 = {left.coordinates[0] + p1_left[0] - p1_right_permute[0],
                            left.coordinates[1] + p1_left[1] - p1_right_permute[1],
                            left.coordinates[2] + p1_left[2] - p1_right_permute[2]};
                        vector<int> right_2 = {left.coordinates[0] + p2_left[0] - p2_right_permute[0],
                            left.coordinates[1] + p2_left[1] - p2_right_permute[1],
                            left.coordinates[2] + p2_left[2] - p2_right_permute[2]};

                        if (right_1 == right_2) {
                            // place the coordinates
                            right.coordinates = right_2;

                            // permute all the beacons to match
                            vector<vector<int>> new_beacons;
                            new_beacons.reserve(right.beacons.size());

                            for (const auto& b : right.beacons) {
                                new_beacons.push_back(permute(d, b));
                            }

                            right.beacons = new_beacons;

                            return;
                        }

                    }
                }
            }
        }
    }


    vector<vector<int>> xyz = right.beacons;

}

// just checks if all scanners are placed
bool all_placed(const vector<Scanner>& sc) {
    return all_of(sc.begin(), sc.end(), [](const Scanner& s) {return s.coordinates.size() == 3;});
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
    scanners.emplace_back(number, beacons);

    // scanner 0 will be our main point
    scanners[0].coordinates = {0,0,0};

    // when not all scanners are placed
    while (!all_placed(scanners)) {
        for (const auto &scanner1 : scanners) {
            // scanner 1 must be placed
            if (scanner1.coordinates.size() != 3) {
                continue;
            }

            for (Scanner &scanner2 : scanners) {
                // if there is overlap, place scanner 2
                if (overlap(scanner1, scanner2) && scanner2.coordinates.size() != 3) {
                    place_scanner(scanner1, scanner2);
                }
            }
        }
    }

    // compute all of the unique points
    set<vector<int>> beacons_unique;
    for (const auto &scanner : scanners) {
        for (auto &beacon : scanner.beacons) {
            beacons_unique.insert({scanner.coordinates[0]+beacon[0],scanner.coordinates[1]+beacon[1],scanner.coordinates[2]+beacon[2]});
        }
    }
    cout << "Part 1: " << beacons_unique.size() << endl;

    int part_2 = 0;

    // find the largerst manhattan distance between any 2 points
    for (const auto &sc1 : scanners) {
        for (const auto &sc2 : scanners) {
            int dist = abs(sc1.coordinates[0]-sc2.coordinates[0]) +
                    abs(sc1.coordinates[1]-sc2.coordinates[1]) +
                    abs(sc1.coordinates[2]-sc2.coordinates[2]);
            part_2 = max(part_2, dist);
        }
    }

    cout << "Part 2: " << part_2 << endl;


}