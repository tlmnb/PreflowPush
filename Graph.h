/* 
 * File:   Graph.h
 * Author: Tilman
 *
 * Created on June 24, 2012, 4:36 PM
 */

#include <vector>
#include <iostream>
#ifndef GRAPH_H
#define	GRAPH_H

class Graph {
public:
    Graph(int V);
    void addEdge(int u, int v, int cuv, int cvu);
private:
    int numberOfNodes;
    std::vector<std::vector<int> > adj; //adjacency matrix
    std::vector<std::vector<int> > cap; //capacity matrix
    friend std::ostream& operator<<(std::ostream&, const Graph&);
};

#endif	/* GRAPH_H */

