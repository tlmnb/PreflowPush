/* 
 * File:   PreflowPushGeneric.h
 * Author: Tilman Wittl
 *
 * Created on 2. Juli 2012, 11:41
 */

#include "Graph.h"



#ifndef PREFLOWPUSHGENERIC_H
#define	PREFLOWPUSHGENERIC_H

class PreflowPushGeneric {
public:
    PreflowPushGeneric(Graph* graph);
    PreflowPushGeneric(const PreflowPushGeneric& orig);
    virtual ~PreflowPushGeneric();
    virtual void exec();
    void print();
    int getMaxFlow();
    
protected:
    Graph* g;
    std::vector<int> h;
    std::vector<int> e;
    bool push(int u, int v);
    bool lift(int u);
    bool isActive(int u);
   
   
private:
    void updateReducedNetwork();
    void init();
    int cf(int u, int v);
    
    // "Zu einem gegebenen Fluss f definieren wir das reduzierte Netzwerk Df,
    // dessen Kanten angeben, zwischen welchen Knoten noch zusätzlicher Nettofluss
    // möglich ist.
    // Die Restkapazität von Knoten u zum Knoten v ist definiert als cf(u,v) = c(u,v) - f(u,v).
    // Das reduzierte Netzwerke Df ist Df=(V,Af) = {(u,v) \in VxV | cf(u,v) > 0}"
    // Skript S. 72
    Graph* reduced;
    
    int source;
    int target;
    int size;   
    std::vector<std::vector<int> > f;
    
};

#endif	/* PREFLOWPUSHGENERIC_H */

