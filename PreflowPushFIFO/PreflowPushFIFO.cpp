/* 
 * File:   PreflowPushFIFO.cpp
 * Author: haas
 * 
 * Created on July 3, 2012, 10:23 AM
 */

#include "PreflowPushFIFO.h"
#include <iterator>

PreflowPushFIFO::PreflowPushFIFO(Graph &g) : PreflowPushGeneric(&g) {
}

PreflowPushFIFO::PreflowPushFIFO(const PreflowPushFIFO& orig): PreflowPushGeneric(orig) {
}

void PreflowPushFIFO::exec() {
    // p. 85
    // "Zu Beginn wird L mit den nach der Initialisierung aktiven Knoten besetzt" 
    // TODO: is there an easier way to get these?
    for (int ii = 0; ii < this->g->getNumberOfNodes(); ii) {
        if (this->isActive(ii))
            this->L.push_back(ii);
    }
    // p. 85
    // "Es wird jeweils für das erste Listenelement Examine aufgerufen"
    for (vector<int>::iterator current = this->L.begin(); current < this->L.end(); current++)
    {
        this->examine(*current);
    } 
}
// method Examine(u), sript page 85
void PreflowPushFIFO::examine(int u) {
    if (this->isActive(u)) {
        // Part 1.1
        // "Solange möglich, führe Operationen Push(u,v) aus."
        bool updated;
        do {
            updated = false;
            // TODO: where does v come from?
            // is neighbors correct here?
            vector<int> neighbors = this->g->getNeighbors(u);
            for (vector<int>::iterator it = neighbors.begin(); it < neighbors.end(); it++)
            {
                updated = (updated || this->push(u, *it));
                // "Wird dabei e[v] > 0, dann füge v an das Ende von L"
                if (this->e[*it] > 0)
                    this->L.push_back(*it);
            }
        } while (updated);
        // Part 1.2
        // "Ist Lift(u) anwendbar, dann führe die Operation aus und setze u an
        // das Endes von L, andernfalls entferne u aus L"
        // (u is already popped from the stack in exec())
        if (this->lift(u)) {
            this->L.push_back(u);
        }
            
    }
        
    
}


PreflowPushFIFO::~PreflowPushFIFO() {
}

