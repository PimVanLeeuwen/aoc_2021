//
// Created by pimvanleeuwen on 11/20/24.
//

#include "Day18.h"

#include <deque>
#include <iostream>
#include <memory>

using namespace std;

// check if a string can explode
bool canExplode(const string& number) {
    int counter = 0;

    for (auto& c : number) {
        if (c == '[') {
            counter++;
        } else if (c == ']') {
            counter--;
        }

        if (counter == 5) {
            return true;
        }
    }

    return false;
}

string explode(const string& number) {
    string result;
    int depth = 0;
    int pointer = 0;
    int left = -1;
    int right = -1;
    bool exploded = false;
    bool placed_right = false;

    // go through all chars
    while (pointer < number.size()) {
        // increase or decrease the depth
        if (number[pointer] == '[') {
            depth++;
        } else if (number[pointer] == ']') {
            depth--;
        }

        // if it is too deep and we have not yet exploded, do that
        if (depth == 5 && !exploded) {
            int temp_pointer = pointer;

            pointer++;
            // add the first number
            if (isdigit(number[pointer+1])) {
                left = stoi(number.substr(pointer, 2));
                pointer += 3;
            } else {
                left = number[pointer] - '0';
                pointer += 2;
            }

            // add the first number
            if (isdigit(number[pointer+1])) {
                right = stoi(number.substr(pointer, 2));
                pointer += 2;
            } else {
                right = number[pointer] - '0';
                pointer += 1;
            }

            // place the zero instead of the pair
            result += '0';

            // we have exploded
            exploded = true;

            // place left number added to the old number
            while (temp_pointer > 0) {
                if (isdigit(result[temp_pointer]) && isdigit(result[temp_pointer - 1])) {
                    const int old_num = stoi(result.substr(temp_pointer-1, 2));
                    int new_num = left + old_num;
                    result.erase(result.begin() + temp_pointer-1, result.begin() + temp_pointer+1);
                    result.insert(temp_pointer - 1, to_string(new_num));
                    break;
                } else if (isdigit(number[temp_pointer])) {
                    const int old_num = number[temp_pointer] - '0';
                    int new_num = left + old_num;
                    result.erase(result.begin() + temp_pointer);
                    result.insert(temp_pointer, to_string(new_num));
                    break;
                }
                temp_pointer--;
            }

        } else if (isdigit(number[pointer]) && exploded && !placed_right) {
            // place the right number
            int old_num;

            if (isdigit(number[pointer+1])) {
                old_num = stoi(number.substr(pointer, 2));
                pointer++;
            } else {
                old_num = number[pointer] - '0';
            }

            result += to_string(old_num + right);

            placed_right = true;
        } else {
            result += number[pointer];
        }

        pointer++;
    }

    return result;
}

// check if a string can split
bool canSplit(const string& number) {
    int counter = 0;

    for (auto& c : number) {
        if (isdigit(c)) {
            counter++;
        } else {
            counter = 0;
        }

        if (counter == 2) {
            return true;
        }
    }

    return false;
}

string split(const string& number) {
    string result;
    bool split = false;


    // go through all chars
    for (int i = 0; i < number.size(); i++) {
        if (isdigit(number[i]) && isdigit(number[i+1]) && !split) {
            const int left = stoi(number.substr(i, 2))/2;
            const int right = (stoi(number.substr(i, 2))+1)/2;
            result += "["+to_string(left)+","+to_string(right)+"]";
            i++;
            split = true;
        } else {
            result += number[i];
        }
    }

    return result;
}

int computeMag(const string& number) {
    // put it in a vector to compute the magnitude
    vector<string> result_vec;

    for (const auto &r : number) {
        string s;
        s += r;
        result_vec.push_back(s);
    }

    while(true) {
        vector<string> new_result_vec;
        for (int i = 0; i < result_vec.size(); i++) {
            if (result_vec[i] == "[" && result_vec[i+4] == "]") {
                new_result_vec.push_back(to_string((3*stoi(result_vec[i+1])) + (2*stoi(result_vec[i+3]))));
                i += 4;
            } else {
                new_result_vec.push_back(result_vec[i]);
            }
        }

        if (result_vec == new_result_vec) {
            break;
        }
        result_vec = new_result_vec;
    }

    return stoi(result_vec[0]);
}


void Day18::execute(const vector<string> &lines) {

    deque<string> numbers;

    for (const auto &line : lines) {
        numbers.push_back(line);
    }

    int max_mag = 0;

    // for part 2 just test every possible thing
    for (const auto &line1 : lines) {
        for (const auto &line2 : lines) {
            string result = "[";
            result += line1;
            result += ",";
            result += line2;
            result += "]";

            // while we can explode or split
            while (canSplit(result) || canExplode(result)) {
                if (canExplode(result)) {
                    result = explode(result);
                } else {
                    result = split(result);
                }
            }

            max_mag = max(max_mag, computeMag(result));

        }
    }

    // then add all numbers for part 1
    string result = numbers.front();
    numbers.pop_front();

    while(!numbers.empty()) {
        const string right = numbers.front();
        numbers.pop_front();
        // add two numbers
        string new_result = "[";
        new_result += result;
        new_result += ",";
        new_result += right;
        new_result += "]";
        result = new_result;

        // while we can explode or split
        while (canSplit(result) || canExplode(result)) {
            if (canExplode(result)) {
                result = explode(result);
            } else {
                result = split(result);
            }
        }
    }



    cout << "Part 1: " << computeMag(result) << endl;
    cout << "Part 2: " << max_mag << endl;
}