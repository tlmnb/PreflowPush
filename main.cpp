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
#include "PreflowPushGeneric.h"
using namespace std;

void printHelp() {
    std::cout << "Usage: $ ./preflowPush -f [graph] -a [random|FIFO|Highest-Label|Excess-Scaling]" << std::endl;
}

int main(int argc, char** argv) {



    Graph g(5,1,5);
    g.addEdge(1,2,3,0);
    g.addEdge(1,3,3,0);
    g.addEdge(2,4,2,0);
    g.addEdge(3,4,2,0);
    g.addEdge(4,5,1,0);
    cout << g << endl;
    
    PreflowPushGeneric pfg(&g);

    /*std::ifstream sg;
    sg.open("sampleGraph");
    assert (sg.is_open());
    Graph readGraph = Graph(sg);
    sg.close();
   
    cout << "Graph from disk:" << endl;
    cout << g << endl;*/

    return 0;
}

