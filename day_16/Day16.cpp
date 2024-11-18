//
// Created by pimvanleeuwen on 11/15/24.
//

#include "Day16.h"

#include <climits>
#include <cmath>
#include <iostream>
#include <math.h>
#include <numeric>
#include <ostream>
#include <stdexcept>

using namespace std;

long long dtoi(const string &decimal) {
    size_t count = decimal.length()-1;
    long long result = 0;
    for (const char c : decimal) {
        result = (c - '0') ? result + static_cast<long>(pow(2, count)) : result;
        count--;
    }
    return result;
}

long long process_packet(int &part_1, const string &packet, int &pointer) {
    // process the head
    part_1 += dtoi(packet.substr(pointer, 3)); // version
    const int type_ID = dtoi(packet.substr(pointer + 3, 3));

    pointer += 6;

    // literal value
    if (type_ID == 4) {
        string number;
        while (true) {
            if (packet[pointer] == '1') {
                number += packet.substr(pointer + 1, 4);
                pointer += 5;
            } else {
                number += packet.substr(pointer + 1, 4);
                pointer += 5;
                break;
            }
        }
        return dtoi(number);
    }

    // not a literal

    vector<long long> numbers;

    if (packet[pointer] == '1') {
        pointer++;
        // number of sub-packets for operator packet
        const int number_packets = dtoi(packet.substr(pointer, 11));
        pointer += 11;

        for (int i = 0; i < number_packets; i++) {
            numbers.push_back(process_packet(part_1, packet, pointer));
        }
    } else {
        pointer++;
        // total length operator packet
        const int total_length = dtoi(packet.substr(pointer, 15));
        pointer += 15;
        const int start_pointer = pointer;

        while (true) {
            numbers.push_back(process_packet(part_1, packet, pointer));
            if (pointer == start_pointer + total_length) {
                break;
            }
        }
    }

    long long start;

    switch (type_ID) {
        case 0:
            // sum; their value is the sum of the values of their sub-packets. If they only have a single sub-packet, their value is the value of the sub-packet
            start = 0;
            for (const auto num: numbers) {
                start += num;
            }
            return start;
        case 1:
            // product; their value is the result of multiplying together the values of their sub-packets. If they only have a single sub-packet, their value is the value of the sub-packet
            start = 1;
            for (const auto num: numbers) {
                start *= num;
            }
            return start;
        case 2:
            // min; their value is the minimum of the values of their sub-packets
            start = LLONG_MAX;
            for (const auto num: numbers) {
                start = min(start, num);
            }
            return start;
        case 3:
            // max; their value is the maximum of the values of their sub-packets
            start = LLONG_MIN;
            for (const auto num: numbers) {
                start = max(start, num);
            }
            return start;
        case 5:
            // greater than; their value is 1 if the value of the first sub-packet is greater than the value of the second sub-packet; otherwise, their value is 0. These packets always have exactly two sub-packets
            if (numbers[0] > numbers[1]) {
                return 1;
            }
            return 0;
        case 6:
            // less than; their value is 1 if the value of the first sub-packet is less than the value of the second sub-packet; otherwise, their value is 0. These packets always have exactly two sub-packets
            if (numbers[0] < numbers[1]) {
                return 1;
            }
            return 0;
        case 7:
            // equal; their value is 1 if the value of the first sub-packet is equal to the value of the second sub-packet; otherwise, their value is 0. These packets always have exactly two sub-packets
            if (numbers[0] == numbers[1]) {
                return 1;
            }
            return 0;
        default:
            throw domain_error("Invalid input");
    }
}

void Day16::execute(const vector<string> &lines) {
    const string &input = lines[0];
    string input_dec;
    int part_1 = 0;

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

    int pointer = 0;

    const long part_2 = process_packet(part_1, input_dec, pointer);

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;

}