/* 
 * File:   ProblemTest.cpp
 * Author: haas
 *
 * Created on 2. Juli 2012, 12:22
 */

#include "ProblemTest.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include "Graph.h"
#include <sstream>
//#include "PreflowPushGeneric.h"

#include <unistd.h>

using namespace std;

bool ProblemTest::test(string file, int desiredFlow) {
    ifstream in;
    string fileName = string("testdat/fprobs/" + file);
    in.open(fileName.c_str());
    Graph g(in);
    //  ALG pfg = alg(g);
    // int flow = pfg.getMaxFlow();
    int flow = 0;
    bool ok = (desiredFlow == flow);
    if (ok)
        cout << "Correct flow for problem " << file << endl;
    else {
        cout << "Wrong flow for problem " << file << endl;
        cout << "Desired flow: " << desiredFlow << " Actual: " << flow << endl;
    }
    return ok;
}

int ProblemTest::testAll() {

    int fail = 0;
    for (int ii = 0; ii < COUNT; ii++) {
        // construct proper file name.
        string file = "";
        int index = ii + 1;
        if (index < 10) {
            file += "0";
        }
        // convert int to string
        stringstream ss;
        ss << index;
        file += ss.str();
        int desiredFlow = results[ii];
        if (!test(file, desiredFlow))
            fail++;
    }
    return fail;
}

/*
 * 
 */
int ProblemTest::run() {
    /*
     optima.txt:

    Optimalwerte zu den Testinstanzen:
    prob.01 2895
    prob.02 12532
    prob.03 273
    prob.04 1429
    prob.05 3642
    prob.06 427
    prob.07 136
    prob.08 2
    prob.09 485
    prob.10 226 */
    results.push_back(2895);
    results.push_back(12532);
    results.push_back(273);
    results.push_back(1429);
    results.push_back(3642);
    results.push_back(427);
    results.push_back(136);
    results.push_back(2);
    results.push_back(485);
    results.push_back(226);

    int failed = testAll();
    if (failed == 0) {
        cout << "All tests passed. Yay!" << endl;
        return 0;
    } else {
        cout << failed << " out of " << COUNT << " tests failed." << endl;
        return failed;
    }
}
