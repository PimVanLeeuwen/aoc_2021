#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void part_1(const string& lines) {

    istringstream stream(lines);

    string line;
    int prev_num = -1;
    int increasing = 0;

    while (getline(stream, line)) {
        if (prev_num == -1) {
            prev_num = stoi(line);
        } else {
            if (stoi(line) > prev_num) {
                increasing++;
            }

            prev_num = stoi(line);
        }

    }
    cout << "Part 1: " << increasing << endl;
}

void part_2(const string& lines) {
    cout << "Part 2: " << "TODO" << endl;
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


