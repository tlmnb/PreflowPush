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
    Graph(int V,int t, int s);
    Graph(std::istream &inFile);
    void addEdge(int u, int v, int cuv, int cvu);
    int getNumberOfNodes();
    std::vector<std::vector<int> > getAdjacencyMatrix();
    std::vector<std::vector<int> > getCapacityMatrix();
    int getSource();
    int getTarget();
    std::vector<int> getNeighbors(int node);
    int getCapacity(int u, int v);
    bool hasEdge(int u, int v);
    bool hasUndirectedEdge(int u, int v);
private:
    int numberOfNodes;
    int source;
    int target;
    std::vector<std::vector<int> > adj; //adjacency matrix
    std::vector<std::vector<int> > cap; //capacity matrix
    friend std::ostream& operator<<(std::ostream&, const Graph&);
    void resize(int V);
};

#endif	/* GRAPH_H */

