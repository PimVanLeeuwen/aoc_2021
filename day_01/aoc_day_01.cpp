#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void part_1(const string& lines) {

    // stream of lines
    istringstream stream(lines);
    string line;

    // convert to vector of numbers
    vector<int> nums;

    while (stream >> line) {
        nums.push_back(stoi(line));
    }

    // two counters for part 1 and part 2
    int increasing_part_1 = 0;
    int increasing_part_2 = 0;

    // count window size 1 and window size 3
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] > nums[i-1]) {
            ++increasing_part_1;
        }

        if (i > 2 && (nums[i-1]+nums[i-2]+nums[i] > nums[i-1]+nums[i-2]+nums[i-3])) {
            ++increasing_part_2;
        }
    }

    // output the results
    cout << "Part 1: " << increasing_part_1 << endl;
    cout << "Part 2: " << increasing_part_2 << endl;
}

void part_2(const string& lines) {

}

int main() {
    fstream file; // define the file
    file.open("../day_01/input.txt", ios::in); // open the file

    // throw an error if it does not open
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    // convert the file to a string
    stringstream buffer;
    buffer << file.rdbuf();
    string lines = buffer.str();

    // close the file, not needed from this point on
    file.close();

    // do part 1
    part_1(lines);

    // do part 2
    part_2(lines);

    return 0;
}


