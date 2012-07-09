/* 
 * File:   PreflowPushHighestLabel.cpp
 * Author: haas
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

PreflowPushHighestLabel::Comperator::Comperator(PreflowPushHighestLabel* phl) {
    (*this).phl = phl;
}

bool PreflowPushHighestLabel::Comperator::operator ()(const int& a, const int& b) {
    return (*this).phl->getH(a) < (*this).phl->getH(b);
}


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
    
PreflowPushHighestLabel::PreflowPushHighestLabel(const PreflowPushHighestLabel& orig) : PreflowPushGeneric(orig) {
}

PreflowPushHighestLabel::~PreflowPushHighestLabel() {
}

    




