//
// Created by pimvanleeuwen on 11/10/24.
//

#include "Day5.h"

#include <iostream>
#include <ostream>
#include <sstream>

class BingoCard;
using namespace std;

class Point {
public:
    int x;
    int y;

    explicit Point(const int _x, const int _y) : x(_x), y(_y) {
    }
};

// print a point
ostream &operator<<(ostream &os, const Point &p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

class CloudGrid {
public:
    // the grid
    vector<vector<int> > h_grid;
    vector<vector<int> > hd_grid;

    // constructor
    explicit CloudGrid(const int size) : h_grid(vector<vector<int> >(size, vector<int>(size, 0))),
                                         hd_grid(vector<vector<int> >(size, vector<int>(size, 0))) {
    }

    void addLine(const Point p1, const Point p2) {
        if (p1.x == p2.x && p1.y == p2.y) {
            throw invalid_argument("two same coordinates");
        } else if (p1.x == p2.x) {
            for (int y = min(p1.y, p2.y); y <= max(p1.y, p2.y); y++) {
                h_grid[y][p1.x] += 1;
                hd_grid[y][p1.x] += 1;
            }
        } else if (p1.y == p2.y) {
            for (int x = min(p1.x, p2.x); x <= max(p1.x, p2.x); x++) {
                h_grid[p1.y][x] += 1;
                hd_grid[p1.y][x] += 1;
            }
        } else {
            // our target point
            int x = p1.x;
            int y = p1.y;

            // go from the one point to the other
            while (x != p2.x || y != p2.y) {
                hd_grid[y][x] += 1;
                x = (x < p2.x) ? x + 1 : x - 1;
                y = (y < p2.y) ? y + 1 : y - 1;
            }
            hd_grid[y][x] += 1;
        }
    }

    [[nodiscard]] int part1() const {
        int counter = 0;

        for (const vector<int> &row: h_grid) {
            for (const int x: row) {
                if (x > 1) {
                    counter++;
                }
            }
        }

        return counter;
    }

    [[nodiscard]] int part2() const {
        int counter = 0;

        for (const vector<int> &row: hd_grid) {
            for (const int x: row) {
                if (x > 1) {
                    counter++;
                }
            }
        }

        return counter;
    }
};


void Day5::part_1(const vector<string> &lines) {
    auto grid = CloudGrid(1000);

    // get all the points
    for (const auto &line: lines) {
        // convert into a string stream to split on token
        // for this we converted -> to , in the input file
        stringstream ss(line);
        string token;

        // put the points in here
        vector<int> points;

        // separate line
        while (getline(ss, token, ',')) {
            points.push_back(stoi(token));
        }

        // add the line to the grid
        grid.addLine(Point(points[0], points[1]), Point(points[2], points[3]));
    }


    cout << "Part 1: " << grid.part1() << endl;
    cout << "Part 2: " << grid.part2() << endl;
}

void Day5::part_2(const vector<string> &lines) {
}
