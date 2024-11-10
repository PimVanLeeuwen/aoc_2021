//
// Created by pimvanleeuwen on 11/9/24.
//

#include "Day4.h"

#include <iostream>

using namespace std;

class BingoCard {
public:
    // the actual numbers
    vector<vector<int>> numbers;

    // constructor
    explicit BingoCard(const vector<vector<int> > &param_numbers) : numbers(param_numbers) {
    }

    // check if the card has bingo
    [[nodiscard]] bool hasBingo() const {
        // check for each column/row
        for (int i = 0; i < 5; ++i) {
            // if this row/column
            bool row_bingo = true;
            bool col_bingo = true;
            for (int j = 0; j < 5; ++j) {
                // check if there is a non -1 in a row
                if (numbers[i][j] != -1) {
                    row_bingo = false;
                }

                // check if there is a non -1 in a column
                if (numbers[j][i] != -1) {
                    col_bingo = false;
                }
            }

            // return if there is bingo
            if (row_bingo || col_bingo) {
                return true;
            }

        }

        return false;
    }

    void removeNumber(const int n) {
        // check for each cell
        for (int i = 0; i < 5; ++i) {
            // if the number matches n, remove it then
            for (int j = 0; j < 5; ++j) {
                if (numbers[i][j] == n) {
                    numbers[i][j] = -1;
                }
            }
        }
    }

    [[nodiscard]] int computeScore() const {
        int score = 0;
        // check for each cell
        for (int i = 0; i < 5; ++i) {
            // if the number matches n, remove it then
            for (int j = 0; j < 5; ++j) {
                if (numbers[i][j] != -1) {
                    score += numbers[i][j];
                }
            }
        }

        return score;
    }

    [[nodiscard]] bool hadBingo() const {
        return bingo;
    }

    void setBingo() {
        bingo = true;
    }
private:
    bool bingo = false;
};

// Add this to print the bingo cards
ostream &operator<<(ostream &os, const BingoCard &bingoCard) {
    os << "= Bingo Card =" << endl;
    for (const vector<int>& row : bingoCard.numbers) {
        for (const int row_number : row) {
            if (row_number > 9) {
                os << row_number << " ";
            } else {
                os << " " << row_number << " ";
            }
        }
        os << endl;
    }
    os << "==============" << endl;
    return os;
}

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
    vector<vector<int>> bingo_card;

    // Vector storing the bingo cards
    vector<BingoCard> cards;

    for (string line : lines_edit) {
        if (line.empty()) {
            // At an empty line we split the bingo cards and add it to the list
            cards.emplace_back(bingo_card); // This creates a BingoCard object since cards contains just that
            bingo_card.clear(); // clear the one that we were building
        } else {
            vector<int> row;

            // loop and convert them
            pos = 0;
            while (pos < line.size()) {
                pos = line.find(' '); // NOLINT(*-narrowing-conversions)
                if (pos > 0) {
                    row.push_back(stoi(line.substr(0,pos)));
                }
                line.erase(0,pos+1);
            }

            // push the final number
            row.push_back(stoi(line));

            // push the row to the bingo card
            bingo_card.push_back(row);
        }
    }

    // go through all the numbers
    int bingo_count = 0;

    for (int bingo_number : lines_1_vec) {
        // check each card
        for (auto& card : cards) {
            card.removeNumber(bingo_number);

            // if the card has bingo, process it
            if (card.hasBingo() && !card.hadBingo()) {
                // keep count
                bingo_count++;
                // mark as bingo
                card.setBingo();

                // print the first for part 1
                if (bingo_count == 1) {
                    cout << "Part 1: " << card.computeScore()*bingo_number << endl;
                }

                // print the second for part 2
                if (bingo_count == cards.size()) {
                    cout << "Part 2: " << card.computeScore()*bingo_number << endl;
                }
            }

        }
    }
}

void Day4::part_2(const vector<string>& lines) {
    }
