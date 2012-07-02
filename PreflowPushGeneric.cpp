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
    (*this).updateReducedNetwork();
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
    std::vector<std::vector<int> > adj = (*this).g->getAdjacencyMatrix();
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
    (*this).red.resize(a, std::vector<int>(a, 0));
}

void PreflowPushGeneric::updateReducedNetwork() {
    //compute reduced network. c.f. Cormen et. al, 2001
    for(int u=0; u<(*this).g->getNumberOfNodes(); u++) {
        for(int v=0; v<(*this).g->getNumberOfNodes(); v++) {
            if((*this).g->hasUndirectedEdge(u,v)) {
                if( ((*this).g->getCapacity(u,v)-(*this).f[u][v])>0) {
                        (*this).red[u][v]=1;
                }
            }
        }
    }
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
    int cf = (*this).g->getCapacity(u,v)-(*this).f[u][v];
    if((*this).isActive(u) && (*this).h[u]==(*this).h[v]+1 && cf>0) {
        int delta = std::min((*this).e[u],cf);
        (*this).f[u][v] = (*this).f[u][v] + delta;
        (*this).f[v][u] = -(*this).f[u][v];
        (*this).e[u] = (*this).e[u] - delta;
        (*this).e[v] = (*this).e[v] + delta;
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
    for(int v=0; v<(*this).red[u].size(); v++) {
        if((*this).h[u] > (*this).h[v]) {
            hasNoEdge = true;
            break;
        }
    }
    if((*this).isActive(u) && !hasNoEdge) {
        //TODO
        
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

void PreflowPushGeneric::exec(){
    // Does not do anything. TODO: this is supposed to be abstract,
    // but I don't know how that is done in C++.
}

PreflowPushGeneric::PreflowPushGeneric(const PreflowPushGeneric& orig) {
}

PreflowPushGeneric::~PreflowPushGeneric() {
}

