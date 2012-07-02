/* 
 * File:   main.cpp
 * Author: Tilman
 *
 * Created on June 24, 2012, 4:24 PM
 */


#include <iostream> 
#include <unistd.h>
#include <fstream>
#include "Graph.h"
#include <assert.h>
#include "ProblemTest.h"
#include <fstream>
#include "PreflowPushGeneric.h"
using namespace std;

void printHelp() {
    std::cout << "Usage: $ ./preflowPush -f [graph] -a [Random|FIFO|Highest-Label|Excess-Scaling|Run-Tests]" << std::endl;
}

int main(int argc, char** argv) {        
    if (argc < 5 || string(argv[1]) != string("-f") || string(argv[3]) != string("-a"))
    {
        printHelp();
        exit(1);
    }
        
    string graphFile = argv[2];
    ifstream in(graphFile.c_str());
    Graph inputGraph(in);
    string algType = argv[4];
    
    if (algType == "Random"){
        cerr << "Not implemented." << endl;
    }
    else if (algType == "FIFO")
    {
        cerr << "Not implemented." << endl;
    }
    else if (algType == "Highest-Label"){
        cerr << "Not implemented." << endl;
    }
    else if (algType == "Excess-Scaling"){
        cerr << "Not implemented." << endl;
    }
    else if (algType == "Run-Tests")
    {
        cout << "Running tests..." << endl;
        ProblemTest tester;
        tester.run();
    } else if (algType == "Moo") {
        cout << "        (__)" << endl;
        cout << "        (oo)" << endl;
        cout << "  /------\\/" << endl;
        cout << " / |    ||" << endl;
        cout << "*  /\\---/\\" << endl;
        cout << "   ~~   ~~ " << endl;
    } else
    {
        std::cout << "Unknown algorithm type." << std::endl;
    }
   
    Graph g(5,1,5);
    g.addEdge(1,2,3,0);
    g.addEdge(1,3,3,0);
    g.addEdge(2,4,2,0);
    g.addEdge(3,4,2,0);
    g.addEdge(4,5,1,0);
    cout << g << endl;
    PreflowPushGeneric pfg(&g);

    return 0;
}

