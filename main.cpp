#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "day_1/Day1.h"
#include "day_2/Day2.h"
#include "day_3/Day3.h"
#include "day_4/Day4.h"
#include "day_5/Day5.h"
#include "day_6/Day6.h"
#include "day_7/Day7.h"
#include "day_8/Day8.h"
using namespace std;

int main() {
    int day_input;

    cout << "Input the day please: ";
    cin >> day_input;

    fstream file; // define the file
    file.open("../day_" + to_string(day_input) + "/input.txt", ios::in); // open the file

    vector<string> lines;
    string line;


    // throw an error if it does not open
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    while (getline(file, line)) {
        lines.push_back(line);
    }

    // close the file, not needed from this point on
    file.close();

    switch (day_input) {
        case 1:
            Day1::execute(lines);
            break;
        case 2:
            Day2::execute(lines);
            break;
        case 3:
            Day3::execute(lines);
            break;
        case 4:
            Day4::execute(lines);
            break;
        case 5:
            Day5::execute(lines);
            break;
        case 6:
            Day6::execute(lines);
            break;
        case 7:
            Day7::execute(lines);
            break;
        case 8:
            Day8::execute(lines);
            break;
        default:
            cerr << "Error opening class corresponding to day" << endl;
            return 1;
    }
  return 0;
}