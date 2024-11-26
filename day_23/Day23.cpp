//
// Created by pimvanleeuwen on 11/26/24.
//

#include "Day23.h"

using namespace std;

int solve(vector<vector<char>> &map, int cost) {return 0;}

void Day23::execute(const vector<string> &lines) {
    // ps I know they are not snails, but it writes easier
    // this is the map of the snails
    vector<vector<char>> map = {{'#','#','#','#','#','#','#','#','#','#','#','#','#'},
    {'#','.','.','.','.','.','.','.','.','.','.','.','#'},
    {'#','#','#','D','#','B','#','D','#','B','#','#','#'},
    {'#','#','#','C','#','A','#','A','#','C','#','#','#'},
    {'#','#','#','#','#','#','#','#','#','#','#','#','#'}};

    // x,y pairs to consider as valid places for snails
    vector<pair<int,int>> {{1,1}, {2,1}, {4,1}, {6,1}, {8,1},
        {10,1},{11,1}, {3,2}, {3,3}, {5,2}, {5, 3},
    {7,2}, {7,3}, {9,2}, {9,3}};



}
