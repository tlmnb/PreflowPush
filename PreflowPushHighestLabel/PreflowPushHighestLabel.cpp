/* 
 * File:   PreflowPushHighestLabel.cpp
 * Author: haas
 * 
 * Created on July 3, 2012, 1:52 PM
 */

#include "PreflowPushHighestLabel.h"
#include <algorithm>

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
    std::vector<int> nodes; //all nodes
    for(int i=0; i<(*this).g->getNumberOfNodes(); i++) {
        nodes.push_back(i);
    }
    
    Comperator comp(this);
    std::make_heap(nodes.begin(),nodes.end(),comp);
    
}


