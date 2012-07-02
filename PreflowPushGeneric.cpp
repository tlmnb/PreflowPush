/* 
 * File:   PreflowPushGeneric.cpp
 * Author: Tilman Wittl
 * 
 * Created on 2. Juli 2012, 11:41
 */

#include "PreflowPushGeneric.h"
#include "Graph.h"

PreflowPushGeneric::PreflowPushGeneric(Graph* graph) {
    (*this).g = graph;
    int a = (*this).g->getNumberOfNodes();
    (*this).h.resize(a,0); // set h for all nodes to 0
    (*this).e.resize(a,0); // set e for all nodes to 0
    (*this).f.resize(a, std::vector<int>(a, 0)); //define "function" f
    std::vector<std::vector<int> > adj = (*this).g->getAdjacencyMatrix();
    for(int u=0; u<adj.size(); u++) {
        for(int v=0; v<adj[u].size(); v++) {
            if(adj[u][v]>0) {
                f[u][v]=0;
                f[v][u]=0;
                
            }
        }
    }
    (*this).red.resize(a, std::vector<int>(a, 0));
    (*this).source = (*this).g->getSource();
    (*this).target = (*this).g->getTarget();
    (*this).h[(*this).source] = a;
    std::vector<int> neighborsOf = (*this).g->getNeighbors(source);
    for(int i=0; i<neighborsOf.size(); i++) {
        int v = neighborsOf[i];
        (*this).f[(*this).source][v] = (*this).g->getCapacity((*this).source,v);
        (*this).f[v][(*this).source] = -(*this).g->getCapacity((*this).source,v);
        (*this).e[v] = (*this).g->getCapacity((*this).source,v);
    }
    (*this).updateReducedNetwork();
}


void PreflowPushGeneric::updateReducedNetwork() {
    //compute reduced network. c.f. Cormen et. al, 2001
    /*for(int u=0; u<(*this).g->getNumberOfNodes(); u++) {
        for(int v=0; v<(*this).g->getNumberOfNodes(); v++) {
            if(this->g->hasUndirectedEdge(v,u)) {
                if ((this->g->getCapacity(u,v)+f[v][u])>0) {
                    std:: cout << u << "->" << v << std::endl;
                }
            }
        }
    }
    for(int u=0; u<(*this).g->getNumberOfNodes(); u++) {
        for(int v=0; v<(*this).g->getNumberOfNodes(); v++) {
            if ((*this).red[u][v]==1) {
                //std::cout << u << "->" << v << std::endl;
            }
        }
    }*/
}


PreflowPushGeneric::PreflowPushGeneric(const PreflowPushGeneric& orig) {
}

PreflowPushGeneric::~PreflowPushGeneric() {
}

