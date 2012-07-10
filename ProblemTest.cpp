/* 
 * File:   ProblemTest.cpp
 * Author: Michael Haas
 *
 * Tests the algorithms with the supplied test graphs and compares the computed
 * max flow with correct values.
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
#include "PreflowPushFIFO/PreflowPushFIFO.h"
#include "PreflowPushRandom/PreflowPushRandom.h"
#include "PreflowPushHighestLabel/PreflowPushHighestLabel.h"
#include <unistd.h>
#include "Timer.h"


using namespace std;

void print(Timer &t, int flow, int desiredFlow) {
 
    cout << "Maxflow calculation took " << t.duration() << "ms" << endl;
    
    if (flow == desiredFlow)
        cout << "Flow correct!" << endl;
    else
        cout << "Flow incorrect. Desired: " << desiredFlow << ", Actual: " << flow << endl;
}

void ProblemTest::test(string file, int desiredFlow) {
    Timer t;
    ifstream in;
    string fileName = string("testdata/fprobs/prob." + file);
    cout << "Now reading file " << fileName << endl;
    in.open(fileName.c_str());
    Graph g(in);
    cout << "Finished reading file." << endl;
    cout << "Graph statistics:" << endl;
    cout << "\tNumber of nodes: "  << g.getNumberOfNodes() << endl;
    cout << "\tNumber of edges: " << g.getNumberOfEdges() << endl;
    cout << "\tAverage degree: " << g.getAverageDegree() << endl;
    cout << "\tDensity: " << g.getDensity() << endl;
    
    
    cout << "Testing PreflowPushFifo." << endl;
    t.start();
    PreflowPushFIFO pfg(&g);
    pfg.exec();
    int flow = pfg.getMaxFlow();
    t.stop();
    print(t, flow, desiredFlow);
    
    cout << "Testing PreflowPushRandom" << endl;
    t.start();
    PreflowPushRandom pfr(&g);
    pfr.exec();
    flow = pfr.getMaxFlow();
    t.stop();
    print(t, flow, desiredFlow);
    
    //cout << "Testing PreflowPushHighestLabel" << endl;
    //t.start();
    //PreflowPushHighestLabel pfhl(&g);
    //pfhl.exec();
    //flow = pfhl.getMaxFlow();
    //t.stop();
    //print (t, flow, desiredFlow);
}

void ProblemTest::testAll() {

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
        test(file, desiredFlow);
    }
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

    testAll();
    return 0;
    
}
