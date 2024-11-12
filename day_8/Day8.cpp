//
// Created by pimvanleeuwen on 11/12/24.
//

#include "Day8.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>

using namespace std;

class DigitDisplay {
public:
    // the actual numbers
    vector<string> reference;
    vector<string> output;

    // constructor
    explicit DigitDisplay(const vector<string> &reference, const vector<string> &output) : reference(reference),
        output(output) {
    }

    // solver for part 1
    [[nodiscard]] int count_1478() const {
        int result = 0;
        for (const auto &s: output) {
            if (s.size() == 2 || s.size() == 4 || s.size() == 3 || s.size() == 7) {
                result++;
            }
        }

        return result;
    }

    // solver for part 2
    int solve() {
        string str = "abcdefgh";
        // check each possible permutation
        while (next_permutation(str.begin(), str.end())) {
            // if this is the valid permutation
            if (valid_mapping(str)) {
                vector<int> digits;
                // translate all the output strings with the ref
                for (const auto &out: output) {
                    // make the target, and sort that
                    string ref_target;
                    for (const auto &c: out) {
                        ref_target += str[char_to_int[c]];
                    }
                    sort(ref_target.begin(), ref_target.end());

                    // give back the digits
                    digits.push_back(mapping[ref_target]);
                }

                return 1000 * digits[0] + 100 * digits[1] + 10 * digits[2] + digits[3];
            }
        }

        // this should not happen if everything is solvable
        throw invalid_argument("not solvable input");
    }

    // check if a string is a valid permutation
    bool valid_mapping(const string &p) {
        // for each word in the reference
        for (const auto &ref: reference) {
            // make the target, and sort that
            string ref_target;
            for (const auto &c: ref) {
                ref_target += p[char_to_int[c]];
            }
            sort(ref_target.begin(), ref_target.end());

            // if this is not a valid permutation of the input, return false
            if (mapping.find(ref_target) == mapping.end()) {
                return false;
            }
        }

        // the same for the output
        for (const auto &out: output) {
            // make the target, and sort that
            string out_target;
            for (const auto &c: out) {
                out_target += p[char_to_int[c]];
            }
            sort(out_target.begin(), out_target.end());

            // if this is not a valid permutation of the input, return false
            if (mapping.find(out_target) == mapping.end()) {
                return false;
            }
        }

        return true;
    }

private:
    map<string, int> mapping = {
        {"abcefg", 0},
        {"cf", 1},
        {"acdeg", 2},
        {"acdfg", 3},
        {"bcdf", 4},
        {"abdfg", 5},
        {"abdefg", 6},
        {"acf", 7},
        {"abcdefg", 8},
        {"abcdfg", 9},
    };

    map<char, int> char_to_int = {
        {'a', 0},
        {'b', 1},
        {'c', 2},
        {'d', 3},
        {'e', 4},
        {'f', 5},
        {'g', 6},
        {'h', 7},
    };
};

// Add this to print the bingo cards
ostream &operator<<(ostream &os, const DigitDisplay &digitDisplay) {
    os << "= DigitDisplay =" << endl;
    os << "Reference: ";
    for (const string &ref: digitDisplay.reference) {
        os << ref << " ";
    }
    os << endl;
    os << "Output: ";
    for (const string &out: digitDisplay.output) {
        os << out << " ";
    }
    os << endl;
    return os;
}

void Day8::execute(const vector<string> &lines) {
    int part_1 = 0;
    long part_2 = 0;

    // get all the points
    for (const auto &line: lines) {
        // convert into a string stream to split on token
        // for this we converted -> to , in the input file
        stringstream ss(line);
        string token;

        // put the points in here
        vector<string> ref;
        vector<string> out;

        // separate line
        while (getline(ss, token, ' ')) {
            if (token == "|") {
                continue;
            }
            if (ref.size() == 10) {
                out.push_back(token);
            } else {
                ref.push_back(token);
            }
        }

        auto problem = DigitDisplay(ref, out);

        // if we are here anyway might as well collect the results
        part_1 += problem.count_1478();
        part_2 += problem.solve();
    }

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}
