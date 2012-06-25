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
using namespace std;

void printHelp() {
    std::cout << "Usage: $ ./preflowPush -f [graph] -a [random|FIFO|Highest-Label|Excess-Scaling]"<< std::endl;   
}


int main(int argc, char** argv) {

    
    
    Graph g(4);
    g.addEdge(1,2,5,0);
    g.addEdge(1,3,2,0);
    g.addEdge(2,3,5,3);
    g.addEdge(3,4,7,0);
    cout << g;
    return 0;
}

