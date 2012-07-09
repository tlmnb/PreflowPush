/* 
 * File:   PreflowPushHighestLabel.cpp
 * Author: haas
 * 
 * Created on July 3, 2012, 1:52 PM
 */

#include "PreflowPushHighestLabel.h"
#include <algorithm>
#include <queue>

PreflowPushHighestLabel::PreflowPushHighestLabel(Graph* g) :  PreflowPushGeneric(g) {
}

PreflowPushHighestLabel::PreflowPushHighestLabel(const PreflowPushHighestLabel& orig) : PreflowPushGeneric(orig) {
}

PreflowPushHighestLabel::~PreflowPushHighestLabel() {
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
    std::vector<int> nodes = (*this).g->getNeighbors((*this).g->getSource());
    for(std::vector<int>::iterator it = nodes.begin(); it != nodes.end(); it++) {
        if((*this).g->getSource()==*it || (*this).g->getTarget()==*it) {
            continue;
        }
        Q.push(*it);
    }
    bool lifted = false;
    int currentNode;
    while(!Q.empty() || lifted) {
        if(!lifted) {
            currentNode = Q.top();
            Q.pop();
        }
        bool applied;
        do {
            applied=false;
            std::vector<int> neighbors = (*this).g->getNeighbors(currentNode);
            std::vector<int>::iterator it;
            for(it=neighbors.begin(); it != neighbors.end(); it++) {
                
                applied = (applied || this->push(currentNode, *it));
                if((*this).e[*it]>0) {
                    Q.push(*it);
                }
            }
            
        } while(applied);
        lifted = (*this).lift(currentNode);
        if(lifted) {
            Q.push(currentNode);
        }
        lifted = false;
    }
    
}




