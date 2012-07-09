/* 
 * File:   Graph.cpp
 * Author: Tilman Wittl
 * 
 * This class represents a Digraph.
 * 
 * Created on June 24, 2012, 4:36 PM
 */

#include "Graph.h"
#include <vector>
#include <string>
#include <assert.h>
#include <iterator>
#include <sstream>
#include <stdlib.h>
#include <iostream> 
#include <fstream>
//#include <algorithm>


/*
 * Note: We assume, that the nodes are named by numbers in the range between 1 
 * and |V|. The range of the indices of the adjacency matrix is between 0 and 
 * |V|-1, therefore we substract 1 from the numbers we get.
 */
/**
 * Constructor.
 * 
 * @param V number of nodes
 * @param s source for flow
 * @param t target for flow
 */
Graph::Graph(int V,int s, int t) {
    this->resize(V);
    this->source = s-1;
    this->target = t-1;
    this->edgeCount = 0;
}
/**
 * Constructor. Initializes Graph from file.
 * 
 * File must be formatted as described in
 * http://www.iwr.uni-heidelberg.de/groups/comopt/teaching/ss12/effAlgI/ueb/p1.pdf
 * 
 * @param inFile
 */
Graph::Graph(std::ifstream& inFile) {
    int V, a,s,t;
    std::string line;
    
    if(!inFile.eof()) {
        std::getline(inFile, line);
        std::istringstream i(line);
        i >> V >> a;
        (*this).resize(V);
        std::getline(inFile,line);
        std::istringstream j(line);
        j >> s >> t;
        (*this).source = s-1;
        (*this).target = t-1;
    }
    
    int u, v, cuv, cvu;
    std::istringstream *k;
    while(!inFile.eof()) {
        getline(inFile, line);
        k=new std::istringstream(line);
        *k >> u >> v >> cuv >> cvu;
        (*this).addEdge(u,v,cuv,cvu);
        k->clear();
        k->str("");
        k->seekg(0);
    }
}


/**
 * Resizes the underlying data structure.
 * 
 * @param V size of the graph
 */
void Graph::resize(int V) {
     this->numberOfNodes = V;
     (*this).adj.resize(numberOfNodes, std::vector<bool>(numberOfNodes, 0));
     //create the empty capacity matrix
     (*this).cap.resize(numberOfNodes, std::vector<int>(numberOfNodes, 0));
}

/**
 * Adds a weighted edge from u to v to the Graph.
 * 
 * If the last parameter cvu is not 0,
 * an additional edge with weight cvu
 * going from v to u, i.e. backwards,
 * is added to the graph.
 * 
 * @param u Node u
 * @param v Node v
 * @param cuv Weight for edge u->v
 * @param cvu Weight for edge v->u
 */
void Graph::addEdge(int u, int v, int cuv, int cvu) {
    (*this).adj[u - 1][v - 1] = true;
    (*this).cap[u - 1][v - 1] = cuv;
    this->edgeCount++;
    if (cvu > 0) {
        (*this).adj[v - 1][u - 1] = true;
        (*this).cap[v - 1][u - 1] = cvu;
        this->edgeCount++;
    }
}

/**
 * Removes and edge from the Graph.
 * 
 * @param u Node u
 * @param v Node v
 */
void Graph::deleteEdge(int u, int v) {
    (*this).adj[u-1][v-1] = false;
    this->edgeCount--;
}

/**
 * Gets number of nodes.
 * 
 * @return number of nodes
 */
int Graph::getNumberOfNodes() {
    return (*this).numberOfNodes;
}

/**
 * Gets number of edges.
 * 
 * @return number of edges
 *  */
int Graph::getNumberOfEdges()
{
    return this->edgeCount;
}
/**
 * Returns unweighted adjacency matrix of the graph.
 * 
 * @return adjacency matrix
 */
std::vector<std::vector<bool> > Graph::getAdjacencyMatrix() {
    return (*this).adj;
}

/**
 * Returns capacity matrix of the graph.
 * 
 * Refer to @hasEdge() to check for existence
 * of edges before using edge capacities.
 * 
 * @return 
 */
std::vector<std::vector<int> > Graph::getCapacityMatrix() {
    return (*this).cap;
}

/**
 * Returns source for flow in this graph.
 * 
 * @return flow source
 */
int Graph::getSource() {
    return (*this).source;
}

/**
 * 
 * Returns target for flow in this graph.
 * 
 * @return flow target
 */
int Graph::getTarget() {
    return (*this).target;
}

/**
 * Returns capacity between node u and node v
 * 
 * @param u Node u
 * @param v Node v
 * @return capacity
 */
int Graph::getCapacity(int u, int v) {
    return (*this).cap[u][v];
}

/**
 * 
 * Returns neighbors of a node.
 * 
 * @param node Node whose neighbors are returned
 * @return Neighbors of node
 */
std::vector<int> Graph::getNeighbors(int node) {
    std::vector<int> output;
    for(int i=0; i<(*this).adj[node].size(); i++) {
        if((*this).adj[node][i]) {
            output.push_back(i);
        }
    }
    return output;
}

/**
 * Checks whether an edge from u to v exists in the graph.
 * 
 * @param u Node u
 * @param v Node v
 * @return true or false
 */
bool Graph::hasEdge(int u, int v) {
    return ((*this).adj[u][v]);
}

/**
 * Checks if either an edge from u to v or from
 * v to u exists in the graph.
 * 
 * @param u Node u 
 * @param v Node v
 * @return true or false
 */
bool Graph::hasUndirectedEdge(int u, int v) {
    return ((*this).adj[u][v] || (*this).adj[v][u]);
}


/* overwritten << operator
 */
std::ostream& operator<<(std::ostream &strm, const Graph &g) {
    for (int ii = 0; ii < g.numberOfNodes; ii++) {
        for (int jj = 0; jj < g.numberOfNodes; jj++) {
            if (g.adj[ii][jj]) {
                int w = g.cap[ii][jj];
                strm << ii << " -> " << jj << " capacity: " << w << std::endl;
            }
        }
    }
    return strm;
}
