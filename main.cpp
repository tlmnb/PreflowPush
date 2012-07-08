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
#include "PreflowPushRandom/PreflowPushRandom.h"
#include "PreflowPushFIFO/PreflowPushFIFO.h"
#include "PreflowPushHighestLabel/PreflowPushHighestLabel.h"


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
    ifstream in(graphFile.c_str(),ios::in);
    cerr << "Starting to read graph file from disk." << endl;
    Graph inputGraph(in);
    in.close();
    cerr << "Finished reading graph file from disk. " << endl;

    string algType = argv[4];
    
    if (algType == "Random"){
         cerr << "Initializing algorithm" << endl;
        PreflowPushRandom pfr(&inputGraph);
        cerr << "Finished initializing algorithm. Now calculating max flow" << endl;
        pfr.exec();
        cerr << "Finished calculating max flow." << endl;
        cerr << "Max flow is: " << pfr.getMaxFlow() << endl;
        pfr.print();
    }
    else if (algType == "FIFO")
    {
        cerr << "Initializing algorithm" << endl;
        PreflowPushFIFO pff(&inputGraph);
        cerr << "Finished initializing algorithm. Now calculating max flow" << endl;
        pff.exec();
        cerr << "Finished calculating max flow." << endl;
        //pff.print();
        cerr << "Max flow is: " << pff.getMaxFlow() << endl;
        pff.print();
    }
    else if (algType == "Highest-Label"){
        PreflowPushHighestLabel pfhl(&inputGraph);
        pfhl.exec();
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
   /*
    Graph g(5,1,5);
    g.addEdge(1,2,3,0);
    g.addEdge(1,3,3,0);
    g.addEdge(2,4,2,0);
    g.addEdge(3,4,2,0);
    g.addEdge(4,5,1,0);
    cout << g << endl;
    PreflowPushRandom pfg(&g);
    pfg.exec();
    pfg.print();*/
    return 0;
}

