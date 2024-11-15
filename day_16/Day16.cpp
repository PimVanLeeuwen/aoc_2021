//
// Created by pimvanleeuwen on 11/15/24.
//

#include "Day16.h"

#include <cmath>
#include <iostream>
#include <math.h>
#include <ostream>
#include <stdexcept>

using namespace std;

int dtoi(const string& decimal) {
    size_t count = decimal.length()-1;
    int result = 0;
    for (const char c : decimal) {
        result = (c - '0') ? result + static_cast<int>(pow(2, count)) : result;
        count--;
    }
    return result;
}

void Day16::execute(const vector<string> &lines) {
    string input = lines[0];
    string input_dec;

    for (const auto c : input) {
        switch (c) {
            case '0': input_dec += "0000";break;
            case '1': input_dec += "0001";break;
            case '2': input_dec += "0010";break;
            case '3': input_dec += "0011";break;
            case '4': input_dec += "0100";break;
            case '5': input_dec += "0101";break;
            case '6': input_dec += "0110";break;
            case '7': input_dec += "0111";break;
            case '8': input_dec += "1000";break;
            case '9': input_dec += "1001";break;
            case 'A': input_dec += "1010";break;
            case 'B': input_dec += "1011";break;
            case 'C': input_dec += "1100";break;
            case 'D': input_dec += "1101";break;
            case 'E': input_dec += "1110";break;
            case 'F': input_dec += "1111";break;
            default: throw domain_error("Invalid input");
        }
    }

    cout << input_dec << endl;

    int pointer = 0;

    // process the string
    while (pointer < input_dec.length()) {
        // process the head
        int version = dtoi(input_dec.substr(pointer, 3));
        int type_ID = dtoi(input_dec.substr(pointer+3, 3));
        cout << "Version: " << version << endl;
        cout << "Type_ID: " << type_ID << endl;

        pointer += 6;

        // literal value
        if (type_ID == 4) {
            int literal_count = 6;
            while (true) {
                if (input_dec[pointer] == '1') {
                    cout << input_dec.substr(pointer+1, 4)  << endl;
                    pointer += 5; literal_count += 5;
                } else {
                    cout << input_dec.substr(pointer+1, 4)  << endl;
                    pointer += 5; literal_count += 5;
                    break;
                }
            }

            // skip the redundant bits
            pointer = (literal_count % 4 == 0) ? pointer : pointer + 4 - literal_count % 4;
        } else {
            // TODO: other case for the operator
        }
    }

}