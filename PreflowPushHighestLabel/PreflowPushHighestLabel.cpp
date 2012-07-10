/* 
 * File:   PreflowPushHighestLabel.cpp
 * Author: Michael Haas
 * 
 * Implementation of the HighestLabel strategy for the PreflowPush algorithm.
 * See @PreflowPushHighestLabel::exec() for details.
 * 
 * Created on July 3, 2012, 1:52 PM
 */

#include "PreflowPushHighestLabel.h"
#include <algorithm>
#include <queue>

/**
 * Constructor. See superclass for documentation.
 * 
 * @param g
 */
PreflowPushHighestLabel::PreflowPushHighestLabel(Graph* g) :  PreflowPushGeneric(g) {
}

/**
 * 
 * Constructor.
 * 
 * @param phl PreflowPushHighestLabel instance
 */
PreflowPushHighestLabel::Comperator::Comperator(PreflowPushHighestLabel* phl) {
    (*this).phl = phl;
}

/**
 * 
 * Comperator implementation for std::priority_queue.
 * This allows priorisation of nodes with h values for height.
 * 
 * 
 * @param a node a
 * @param b node b
 * @return Whether a is less high than b or not
 */
bool PreflowPushHighestLabel::Comperator::operator ()(const int& a, const int& b) {
    return (*this).phl->getH(a) < (*this).phl->getH(b);
}

/**
 * 
 * Runs the algorithm.
 * 
 * This strategy will always try to push flow from the highest node.
 * For efficient retrieval of the currently highest node, a std::priority_queue
 * is used.
 * 
 * More information can be found on page 85 of Reinelt's script.
 * 
 */
void PreflowPushHighestLabel::exec() {
    Comperator comp(this);
    std::priority_queue<int, std::vector<int>, Comperator> Q(comp);
    
    for(int i=0; i<(*this).g->getNumberOfNodes(); i++) {
        if((*this).isActive(i)) {
                Q.push(i);
        }
    }
    
    while(!Q.empty()) {
        int currentNode = Q.top();
        Q.pop();
        bool updated;
        do {
            updated = false;
            std::vector<int> neighbors = this->g->getNeighbors(currentNode);
            //std::make_heap(neighbors.begin(),neighbors.end(),comp);
            for (std::vector<int>::iterator it = neighbors.begin(); it < neighbors.end(); it++) {
                updated = (updated || this->push(currentNode, *it));
                if ((*this).e[*it]>0) {
                    Q.push(*it);
                }
            }
        } while(updated);
        (*this).lift(currentNode);
            
        
    }
} 

/**
 * Constructor.
 * 
 * See superclass for documentation.
 * @param orig
 */
PreflowPushHighestLabel::PreflowPushHighestLabel(const PreflowPushHighestLabel& orig) : PreflowPushGeneric(orig) {
}

/**
 * Constructor.
 * 
 * See superclass for documentation.
 */
PreflowPushHighestLabel::~PreflowPushHighestLabel() {
}

    




