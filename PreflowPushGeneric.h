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
private:
    Graph* g;
    void updateReducedNetwork();
    void push(int u, int v);
    void lift(int u);
    bool isActive(int u);
    
    int source;
    int target;
    std::vector<int> h;
    std::vector<int> e;
    std::vector<std::vector<int> > f;
    std::vector<std::vector<int> > red;
};

#endif	/* PREFLOWPUSHGENERIC_H */

