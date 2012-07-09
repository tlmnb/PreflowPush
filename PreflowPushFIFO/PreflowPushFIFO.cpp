/* 
 * File:   PreflowPushFIFO.cpp
 * Author: Michael Haas
 * 
 * Implements the FIFO strategy for the PreflowPush algorithm.
 * 
 * Created on July 3, 2012, 10:23 AM
 */

#include "PreflowPushFIFO.h"
#include <iterator>

PreflowPushFIFO::PreflowPushFIFO(Graph* g) : PreflowPushGeneric(g) {
}

PreflowPushFIFO::PreflowPushFIFO(const PreflowPushFIFO& orig): PreflowPushGeneric(orig) {
}

/**
 * Runs the algorithm.
 * 
 * The FIFO strategy maintains a First-In-First-Out queue for nodes.
 * The node at the front of the queue is handed to the examine method.
 * 
 *
 */
void PreflowPushFIFO::exec() {
    // p. 85
    // "Zu Beginn wird L mit den nach der Initialisierung aktiven Knoten besetzt" 
    for (int ii = 0; ii < this->g->getNumberOfNodes(); ii++) {
        if (this->isActive(ii))
        {
            this->L.push(ii);
        }
    }
    // p. 85
    // "Es wird jeweils für das erste Listenelement Examine aufgerufen"
    while ( ! this->L.empty())  {
        int current = this->L.front();
        this->L.pop();
        this->examine(current);
    } 
}
/**
 * Examine method for the FIFO variant of PreflowPush.
 * 
 * This method is called with the node u which comes from the front of the queue.
 * 
 * This method pushes flow from u to its neighbors. If a neighbor
 * becomes active, it is added to the end of the queue.
 * 
 * Node u is then lifted. If the lift operation is successful, node u
 * is added to the end of the queue.
 * 
 * The examine method is described further in Reinelt's script on page 85.
 * 
 * @param u Node u
 */
void PreflowPushFIFO::examine(int u) {
    if (this->isActive(u)) {
        // Part 1.1
        // "Solange möglich, führe Operationen Push(u,v) aus."
        bool updated;
        do {
            updated = false;
            vector<int> neighbors = this->g->getNeighbors(u);
            for (vector<int>::iterator it = neighbors.begin(); it < neighbors.end(); it++)
            {
                updated = (updated || this->push(u, *it));
                // "Wird v dadurch zu einem  Überschussknoten, füge v am Ende von L ein"
                if (this->e[*it] > 0) {
                    this->L.push(*it);
                }
            }
        } while (updated);
        // Part 1.2
        // "Ist Lift(u) anwendbar, dann führe die Operation aus und setze u an
        // das Endes von L, andernfalls entferne u aus L"
        if (this->lift(u)) {
            this->L.push(u);
        }
            
    }
        
    
}

/**
 * Destructor.
 */
PreflowPushFIFO::~PreflowPushFIFO() {
}

