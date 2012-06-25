/* 
 * File:   Graph.cpp
 * Author: Tilman
 * 
 * Created on June 24, 2012, 4:36 PM
 */

#include "Graph.h"
#include <vector>


Graph::Graph(int V) {
    numberOfNodes = V;
    //create the empty adjacency matrix
    std::vector<std::vector<int> > adj(numberOfNodes, std::vector<int>(numberOfNodes,0));
    //create the empty capacity matrix
    std::vector<std::vector<int> > cap(numberOfNodes, std::vector<int>(numberOfNodes,0));
}



void Graph::addEdge(int u, int v, int cuv, int cvu) {
    adj.at(u-1).at(v-1) = 1;
    cap.at(u-1).at(v-1) = cuv;
    if(cvu>0) {
        adj.at(v-1).at(u-1) = 1;
        cap.at(v-1).at(u-1) = cvu;
    }
}

