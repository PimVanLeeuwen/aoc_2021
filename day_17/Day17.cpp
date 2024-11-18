//
// Created by pimvanleeuwen on 11/18/24.
//

#include "Day17.h"

#include <iostream>
#include"z3++.h"


using namespace std;

void Day17::execute(const vector<string> &lines) {
    // ATTEMPT IN Z3 BUT THIS IS NOT REALLY NEEDED, WILL KEEP HERE IN ANY CASE BECAUSE IT IS WORKING Z3 IN C++
    //
    // z3::context c;
    //
    // vector<z3::expr> x;
    // vector<z3::expr> y;
    // vector<z3::expr> vx;
    // vector<z3::expr> vy;
    //
    // z3::solver s(c);
    //
    // z3::expr disjunction_target = c.bool_val(false);
    //
    // for (int i = 0; i < 300; i++) {
    //     x.push_back(c.int_const(("x_" + to_string(i)).c_str()));
    //     y.push_back(c.int_const(("y_" + to_string(i)).c_str()));
    //     vx.push_back(c.int_const(("vx_" + to_string(i)).c_str()));
    //     vy.push_back(c.int_const(("vy_" + to_string(i)).c_str()));
    //     if (i == 0) {
    //         s.add(x[0] == 0);
    //         s.add(y[0] == 0);
    //     } else {
    //         s.add(x[i] == x[i-1] + vx[i-1]);
    //         s.add(y[i] == y[i-1] + vy[i-1]);
    //         s.add(implies(vx[i-1] > 0, vx[i] == vx[i-1] - 1));
    //         s.add(implies(vx[i-1] < 0, vx[i] == vx[i-1] + 1));
    //         s.add(implies(vx[i-1] == 0, vx[i] == vx[i-1]));
    //         s.add(y[i] == y[i-1] - 1);
    //         disjunction_target = disjunction_target || (x[i] <= 73 && x[i] >= 29 && y[i] >= -248 && y[i] <= -194);
    //     }
    // }
    //
    // s.add(disjunction_target);
    //
    // if (s.check() == z3::sat) {
    //     const z3::model m = s.get_model();
    //     cout << "vy_" << 0 << " = " << m.eval(vy[0]) << endl;
    // }
}
