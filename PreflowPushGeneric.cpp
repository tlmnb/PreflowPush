/* 
 * File:   PreflowPushGeneric.cpp
 * Author: Tilman Wittl
 * 
 * Base class for PreflowPush implementations. This class mainly provides
 * Push and Lift operations. The invocation order of these operations is
 * controlled by subclasses.
 * 
 * Created on 2. Juli 2012, 11:41
 */

#include "PreflowPushGeneric.h"
#include "Graph.h"
#include <algorithm>

/**
 * Constructor.
 *  
 * Initializes internal data structures with given graph.
 * 
 * @param graph Graph for which to calculate max flow
 */
PreflowPushGeneric::PreflowPushGeneric(Graph* graph) {

    // erste vier Zeilen
    (*this).g = graph;
    (*this).init();
    //(*this).updateReducedNetwork();
}

/**
 * Initialize data structure.
 * 
 */
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
    (*this).updateReducedNetwork();
}

/**
 * Initialize reduced network.
 */
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

/**
 * 
 * Returns residual capacity between nodes u and v from residual graph.
 * 
 * This is the rest capacity.
 * 
 * @param u Node u
 * @param v Node v
 * @return residual capacity
 */
int PreflowPushGeneric::cf(int u, int v) {
    return ((*this).g->getCapacity(u,v)-(*this).f[u][v]);
}

/**
 * Returns height of node u
 * 
 * @param u
 * @return 
 */
int PreflowPushGeneric::getH(int u) {
    return (*this).h[u];
}

/**
 * 
 * Push operation.
 * 
 * This pushes flow from node u to node v.
 * 
 * It is further described on page 80 in chapter 6.3 of Reinelt's script.
 * 
 * This method returns true if the push operation was possible.
 * The following criteria need to be met:
 * - u must be higher than v
 * - there must be residual capacity from u to v
 * - u must be active
 * 
 * @param u Node u
 * @param v node v
 * @return bool Whether push operation was successful
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
 * 
 * Lift operation.
 * 
 * This operation lifts a node u to allow for
 * more Push operations.
 * 
 * This method returns true if the lift operation was possible.
 * The following criteria must be met:
 * - u must be active
 * - no edge (u,v) in the residual graph with h[u] > h[v]
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


/**
 * Checks whether a given node u is active.
 * 
 * A node is considered active if it is overflowing (and neither source nor
 * target).
 * 
 * @param u Node u
 * @return true or false
 */
bool PreflowPushGeneric::isActive(int u) {
    return (u!=(*this).source && u!=(*this).target && (*this).e[u]>0);
}
/**
 * Runs the algorithm. After this method returns,
 * @getMaxFlow() can be called to obtain the maximum amount of flow
 * between source and target.
 * 
 * Overriden by subclasses.
 * 
 */
void PreflowPushGeneric::exec() { 
}
/**
 * Prints various informations on the graph to stdout.
 */
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

/**
 * Returns the max flow between source and target.
 * 
 * The @exec() method must be run first.
 * 
 * @return max flow between source and target
 */
int PreflowPushGeneric::getMaxFlow(){
    return this->e[this->target];
}

/**
 * Copy constructor.
 * 
 * @param orig
 */
PreflowPushGeneric::PreflowPushGeneric(const PreflowPushGeneric& orig) {
}

/**
 * Constructor.
 */
PreflowPushGeneric::~PreflowPushGeneric() {
}

