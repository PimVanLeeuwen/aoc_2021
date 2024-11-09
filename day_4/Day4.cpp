//
// Created by pimvanleeuwen on 11/9/24.
//

#include "Day4.h"

#include <iostream>

using namespace std;

class BingoCard {
public:
    vector<vector<int>> numbers;
    static bool hasBingo() {
        return true;
    }
    static int computeRemaining() {
        return 2;
    }
};

void Day4::part_1(const vector<string>& lines) {
    vector<string> lines_edit = lines;

    // get the first line out
    string lines_1 = lines_edit[0];

    // this will be the vector of bingo numbers
    vector<int> lines_1_vec;

    // loop and convert them
    int pos = 0;
    while (pos < lines_1.size()) {
        pos = lines_1.find(','); // NOLINT(*-narrowing-conversions)
        lines_1_vec.push_back(stoi(lines_1.substr(0,pos)));
        lines_1.erase(0,pos+1);
    }

    // remove the lines, so only the bingo cards are left
    lines_edit.erase(lines_edit.begin(), lines_edit.begin()+2);

    // make the bingo cards




    cout << "Part 1: ";

    for (const int s : lines_1_vec) {
        cout << s <<",";
    }

    cout << endl;
}

void Day4::part_2(const vector<string>& lines) {
    cout << "Part 2: " << "TODO" << endl;
}
