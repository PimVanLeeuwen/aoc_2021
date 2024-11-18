//
// Created by pimvanleeuwen on 11/18/24.
//

#include "Day17.h"

#include <iostream>
#include"z3++.h"


using namespace std;

void Day17::execute(const vector<string> &lines) {
    std::cout << "find_model_example1\n";
    z3::context c;
    z3::expr x = c.int_const("x");
    z3::expr y = c.int_const("y");
    z3::solver s(c);

    s.add(x >= 1);
    s.add(y < x + 3);
    cout << s.check() << "\n";

    z3::model m = s.get_model();
    cout << m << "\n";
    // traversing the model
    for (unsigned i = 0; i < m.size(); i++) {
        z3::func_decl v = m[i];
        // this problem contains only constants
        assert(v.arity() == 0);
        cout << v.name() << " = " << m.get_const_interp(v) << "\n";
    }
    // we can evaluate expressions in the model.
    cout << "x + y + 1 = " << m.eval(x + y + 1) << "\n";


}