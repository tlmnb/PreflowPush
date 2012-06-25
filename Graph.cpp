/* 
 * File:   Graph.cpp
 * Author: Tilman
 * 
 * Created on June 24, 2012, 4:36 PM
 */

#include "Graph.h"
#include <vector>

/*
 * Note: We assume, that the nodes are named by numbers in the range between 1 
 * and |V|. The range of the indices of the adjacency matrix is between 0 and 
 * |V|-1, therefore we substracted 1 from the numbers we get.
 */
Graph::Graph(int V) {
    numberOfNodes = V;
    //create the empty adjacency matrix
    (*this).adj.resize(numberOfNodes, std::vector<int>(numberOfNodes, 0));
    //create the empty capacity matrix
    (*this).cap.resize(numberOfNodes, std::vector<int>(numberOfNodes, 0));
    
}


/* Method for adding edges to the adjacency matrix.
 */
void Graph::addEdge(int u, int v, int cuv, int cvu) {
    (*this).adj[u-1][v-1] = 1;
    (*this).cap[u-1][v-1] = cuv;
    if(cvu>0) {
        (*this).adj[v-1][u-1] = 1;
        (*this).cap[v-1][u-1] = cvu;
    }
}



/* overwritten << operator
 */
std::ostream& operator<<(std::ostream &strm, const Graph &g) {
    
}