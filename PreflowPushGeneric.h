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
    Graph* g;
    std::vector<int> h;
    std::vector<int> e;
    bool push(int u, int v);
    bool lift(int u);
    bool isActive(int u);
   
   
private:
    void updateReducedNetwork();
    void init();
  
    int source;
    int target;
    int size;   
    std::vector<std::vector<int> > f;
    std::vector<std::vector<int> > red;
};

#endif	/* PREFLOWPUSHGENERIC_H */

