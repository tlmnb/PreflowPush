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
//#include <algorithm>


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
    this->source = 0;
    this->target = 0;
}

Graph::Graph(std::istream &inFile) {
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
                std::back_inserter<std::vector<std::string> >(tokens));
        // TODO: we can convert to int using istringstream, so wedge that into
        // tokenization somehow
        if (!gotHead1) {
            // TODO: what is a?
            int a = atoi(tokens[0].c_str());
            numberOfNodes = atoi(tokens[1].c_str());
            gotHead1 = true;
            continue;
        }
        if (!gotHead2) {
            assert (gotHead1);
            source = atoi(tokens[0].c_str());
            target = atoi(tokens[1].c_str());
            gotHead2 = true;
            continue;
        }
        assert (gotHead2);
        std::cout << "Adding edge: " << tokens[0] << " " << tokens[1] << " " << tokens[2] << " " << tokens[3] << " " << tokens[4] << std::endl;
        addEdge(atoi(tokens[0].c_str()), atoi(tokens[1].c_str()), atoi(tokens[2].c_str()), atoi(tokens[3].c_str()));
    }
}

/* Method for adding edges to the adjacency matrix.
 */
void Graph::addEdge(int u, int v, int cuv, int cvu) {
    (*this).adj[u - 1][v - 1] = 1;
    (*this).cap[u - 1][v - 1] = cuv;
    if (cvu > 0) {
        (*this).adj[v - 1][u - 1] = 1;
        (*this).cap[v - 1][u - 1] = cvu;
    }
}

/* overwritten << operator
 */
std::ostream& operator<<(std::ostream &strm, const Graph &g) {
    for (int ii = 0; ii < g.numberOfNodes; ii++) {
        for (int jj = 0; jj < g.numberOfNodes; jj++) {
            if (g.adj[ii][jj] > 0) {
                int w = g.cap[ii][jj];
                strm << ii << " -> " << jj << " capacity: " << w << std::endl;
            }
        }
    }
    return strm;
}
