/* 
 * File:   PreflowPushGeneric.cpp
 * Author: Tilman Wittl
 * 
 * Created on 2. Juli 2012, 11:41
 */

#include "PreflowPushGeneric.h"
#include "Graph.h"
#include <algorithm>


PreflowPushGeneric::PreflowPushGeneric(Graph* graph) {

    // erste vier Zeilen
    (*this).g = graph;
    (*this).init();
    //(*this).updateReducedNetwork();
}

void PreflowPushGeneric::init() {
    int a = (*this).g->getNumberOfNodes();
    (*this).source = (*this).g->getSource();
    (*this).target = (*this).g->getTarget();
    // PreflowPush: step 1
    (*this).h.resize(a, 0); // set h for all nodes to 0
    (*this).e.resize(a, 0); // set e for all nodes to 0
    // PreflowPush: step 2
    (*this).f.resize(a, std::vector<int>(a, 0)); //define "function" f
    std::vector<std::vector<bool> > adj = (*this).g->getAdjacencyMatrix();
    for (int u = 0; u < adj.size(); u++) {
        for (int v = 0; v < adj[u].size(); v++) {
            if (adj[u][v] > 0) {
                f[u][v] = 0;
                f[v][u] = 0;
            }
        }
    }
    // PreflowPush: step 3
    (*this).h[(*this).source] = a;

    
    
    // PreflowPush: step 4
    std::vector<int> neighborsOf = (*this).g->getNeighbors(source);
    for (int i = 0; i < neighborsOf.size(); i++) {
        int v = neighborsOf[i];
        (*this).f[(*this).source][v] = (*this).g->getCapacity((*this).source, v);
        (*this).f[v][(*this).source] = -(*this).g->getCapacity((*this).source, v);
        (*this).e[v] = (*this).g->getCapacity((*this).source, v);
    }
    // initialize reduced network
    (*this).reduced = new Graph(a,0,0);
    // call updateReducedNetwork for good measure 
    (*this).updateReducedNetwork();
}

void PreflowPushGeneric::updateReducedNetwork() {
    //compute reduced network. c.f. Cormen et. al, 2001
    for(int u=0; u<(*this).g->getNumberOfNodes(); u++) {
        for(int v=0; v<(*this).g->getNumberOfNodes(); v++) {
            //std::cerr << "cf(" << u << "," << v << ") is :" << (*this).cf(u,v) << std::endl;
            if((*this).cf(u,v)>0) {
                (*this).reduced->addEdge(u+1,v+1,0,0);
            }   
        }
    }
}

int PreflowPushGeneric::cf(int u, int v) {
    return ((*this).g->getCapacity(u,v)-(*this).f[u][v]);
}


int PreflowPushGeneric::getH(int idx) {
    return (*this).h[idx];
}

/**
 * 
 * This method returns true if the push operation was possible.
 * 
 * @param u
 * @param v
 * @return bool indicating modification of state
 */
bool PreflowPushGeneric::push(int u, int v) {
    if((*this).isActive(u) && (*this).h[u]==(*this).h[v]+1 && (*this).cf(u,v) >0) {
        // 1.1
        int delta = std::min((*this).e[u], (*this).cf(u,v));
        (*this).f[u][v] = (*this).f[u][v] + delta;
        (*this).f[v][u] = -(*this).f[u][v];
        (*this).e[u] = (*this).e[u] - delta;
        (*this).e[v] = (*this).e[v] + delta;
        
        if((*this).cf(u,v)<=0) {
            (*this).reduced->deleteEdge(u+1,v+1);
        }
        if((*this).cf(v,u)>0) {
            (*this).reduced->addEdge(v+1,u+1,0,0);
        }
        return true;
    }
    // no push operation possible.
    return false;
}

/**
 * This method returns true if the lift operation was possible. 
 * 
 * @param u
 * @return bool indicating modification of state
 */
bool PreflowPushGeneric::lift(int u) {
    bool hasNoEdge = false;
    std::vector<int> nodes = (*this).reduced->getNeighbors(u);
    for(int i=0; i<nodes.size(); i++) {
        int v = nodes[i];
        if((*this).h[u]>(*this).h[v]) {
            hasNoEdge=true;
            break;
        }
    }
    if((*this).isActive(u) && !hasNoEdge) {
        int min;
        if(nodes.empty()) {
            min = 0;
        } else {
            min = (*this).h[nodes[0]];
            for(int i=1; i<nodes.size(); i++) {
                int v = nodes[i];
                if((*this).h[v]<min) {
                    min = (*this).h[v];
                }
            }
        }
        (*this).h[u]= 1+min;
        // lift operation was possible
        return true;
    } else {
        // no lift operation possible
        return false;
    }
        
}


bool PreflowPushGeneric::isActive(int u) {
    return (u!=(*this).source && u!=(*this).target && (*this).e[u]>0);
}

void PreflowPushGeneric::exec() { 
}

void PreflowPushGeneric::print() {
    std::cout << "h" << std::endl;
    for(int i=0; i<(*this).h.size(); i++) {
        std::cout << "h[" << i << "]=" << (*this).h[i] << std::endl;
    }
    std::cout << "e" << std::endl;
    for(int i=0; i<(*this).e.size(); i++) {
        std::cout << "e[" << i << "]=" << (*this).e[i] << std::endl;
    }
    std::cout << "Gf (reduced network)" << std::endl;
    std::cout << *(*this).reduced << std::endl;
    std::cout << "f" << std::endl;
    for(int i=0; i<(*this).f.size(); i++) {
        for(int j=0; j<(*this).f[i].size(); j++) {
            if((*this).g->hasEdge(i,j)) {
                std::cout << "f[" << i << "," << j << "]=" << (*this).f[i][j] << std::endl;
            }
        }
    }
}

int PreflowPushGeneric::getMaxFlow(){
    return this->e[this->target];
}

PreflowPushGeneric::PreflowPushGeneric(const PreflowPushGeneric& orig) {
}

PreflowPushGeneric::~PreflowPushGeneric() {
}

