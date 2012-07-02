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
    
protected:
    bool push(int u, int v);
    bool lift(int u);
    
    std::vector<int> h;
private:
    Graph* g;
    void updateReducedNetwork();
    void init();

    bool isActive(int u);
    
    int source;
    int target;
    int size;
    //std::vector<int> h;
    std::vector<int> e;
    std::vector<std::vector<int> > f;
    std::vector<std::vector<int> > red;
};

#endif	/* PREFLOWPUSHGENERIC_H */

