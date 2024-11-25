//
// Created by pimvanleeuwen on 11/25/24.
//

#include "Day21.h"

#include <iostream>
#include <ostream>

using namespace std;

pair<long, long> throw_die(vector<pair<int, int>>& players, const int player_turn) {
    pair<long, long> wins = {0,0};
    // what to do if someone won
    if (players[0].second >= 21) {
        wins.first++;
        return wins;
    } else if (players[1].second >= 21) {
        wins.second++;
        return wins;
    }

    // these are all possible three combination throws and how often they occur
    const vector<pair<int, int>> throws = {{9,1}, {8,3}, {7,6}, {6,7},
            {5, 6}, {4,3}, {3,1}};

    // all possible three die throws
    for (auto [die_amount, throws_amount] : throws) {
        // apply the throw
        players[player_turn].first += die_amount;
        players[player_turn].first = (players[player_turn].first > 10) ?
            players[player_turn].first - 10 : players[player_turn].first;

        // next player's turn
        players[player_turn].second += players[player_turn].first;
        auto [p1_more, p2_more] = throw_die(players, player_turn ? 0 : 1);
        players[player_turn].second -= players[player_turn].first;

        // undo the throw
        players[player_turn].first -= die_amount;
        players[player_turn].first = (players[player_turn].first < 1) ?
            players[player_turn].first + 10 : players[player_turn].first;

        // add the wins
        wins.first += p1_more*throws_amount;
        wins.second += p2_more*throws_amount;
    }

    return wins;
}

void Day21::execute(const vector<string> &lines) {
    // starting positions and scores
    vector<pair<int, int>> players = {{2,0}, {5,0}};
    int player = 0;

    // starting die position for part 1
    int die_throws = 0;
    int die = 1;

    while (players[0].second < 1000 && players[1].second < 1000) {
        // throw three times
        for (int i = 0; i < 3; i++) {
            players[player].first += die;
            die = (die == 100) ? 1 : die + 1;
            die_throws++;
        }

        // make sure player stays on the board
        players[player].first = ((players[player].first - 1) % 10) + 1;
        // give score
        players[player].second += players[player].first;

        player = player ? 0 : 1;
    }

    // compute score after part 1 game
    const int part_1 = (players[0].second < players[1].second) ? players[0].second*die_throws : players[1].second*die_throws;
    cout << "Part 1: " << part_1 << endl;

    players = {{2,0}, {5,0}};

    // return the largest one
    if (const auto [player_1_wins, player_2_wins] =
        throw_die(players, 0); player_1_wins > player_2_wins) {
        cout << "Part 2: " << player_1_wins << endl;
    } else {
        cout << "Part 2: " << player_2_wins << endl;
    }

}