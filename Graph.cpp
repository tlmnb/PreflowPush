/* 
 * File:   Graph.cpp
 * Author: Tilman
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
 * |V|-1, therefore we substracted 1 from the numbers we get.
 */
Graph::Graph(int V,int s, int t) {
    this->resize(V);
    this->source = s-1;
    this->target = t-1;
}

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

/*Graph::Graph(std::istream &inFile) {
    std::string line;

    bool gotHead1 = false;
    bool gotHead2 = false;

    while (std::getline(inFile, line)) {
        // Taken from StackOverflow: 
        // http://stackoverflow.com/a/237280
        // I'm not even sure how this work - I guess the istream_iterator
        // automatically breaks at whitespaces.
        // We could also use c-style scanf or fscanf.
        // There also is http://www.cplusplus.com/reference/clibrary/cstring/strtok/
        std::vector<std::string> tokens;
        std::istringstream iss(line);

        std::copy(std::istream_iterator<std::string > (iss),
                std::istream_iterator<std::string > (),
                std::back_inserter<std::vector<std::string> >(tokens));std::cout << V << " " << a << std::endl;
        // TODO: we can convert to int using istringstream, so wedge that into
        // tokenization somehow
        if (!gotHead1) {
            // TODO: what is a?
            int a = atoi(tokens[0].c_str());
            this->resize(atoi(tokens[1].c_str()));
            gotHead1 = true;
            continue;
        }
        if (!gotHead2) {
            assert (gotHead1);
            (*this).source = atoi(tokens[0].c_str())-1;
            (*this).target = atoi(tokens[1].c_str())-1;
            gotHead2 = true;
            continue;
        }
        assert (gotHead2);
        std::cout << "Adding edge: " << tokens[0] << " " << tokens[1] << " " << tokens[2] << " " << tokens[3] << std::endl;
        addEdge(atoi(tokens[0].c_str()), atoi(tokens[1].c_str()), atoi(tokens[2].c_str()), atoi(tokens[3].c_str()));
    }
}
 * */

void Graph::resize(int V) {
     this->numberOfNodes = V;
     (*this).adj.resize(numberOfNodes, std::vector<bool>(numberOfNodes, 0));
     //create the empty capacity matrix
     (*this).cap.resize(numberOfNodes, std::vector<int>(numberOfNodes, 0));
}

/* Method for adding edges to the adjacency matrix.
 */
void Graph::addEdge(int u, int v, int cuv, int cvu) {
    (*this).adj[u - 1][v - 1] = true;
    (*this).cap[u - 1][v - 1] = cuv;
    if (cvu > 0) {
        (*this).adj[v - 1][u - 1] = true;
        (*this).cap[v - 1][u - 1] = cvu;
    }
}

void Graph::deleteEdge(int u, int v) {
    (*this).adj[u-1][v-1] = false;
}

int Graph::getNumberOfNodes() {
    return (*this).numberOfNodes;
}

std::vector<std::vector<bool> > Graph::getAdjacencyMatrix() {
    return (*this).adj;
}

std::vector<std::vector<int> > Graph::getCapacityMatrix() {
    return (*this).cap;
}

int Graph::getSource() {
    return (*this).source;
}

int Graph::getTarget() {
    return (*this).target;
}

int Graph::getCapacity(int u, int v) {
    return (*this).cap[u][v];
}

std::vector<int> Graph::getNeighbors(int node) {
    std::vector<int> output;
    for(int i=0; i<(*this).adj[node].size(); i++) {
        if((*this).adj[node][i]) {
            output.push_back(i);
        }
    }
    return output;
}

bool Graph::hasEdge(int u, int v) {
    return ((*this).adj[u][v]);
}

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
