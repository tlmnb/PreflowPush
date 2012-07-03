/* 
 * File:   PreflowPushFIFO.h
 * Author: haas
 *
 * Created on July 3, 2012, 10:23 AM
 */

#ifndef PREFLOWPUSHFIFO_H
#define	PREFLOWPUSHFIFO_H

#include "PreflowPushGeneric.h"
#include <vector>

using namespace std;

class PreflowPushFIFO: PreflowPushGeneric {
public:
    PreflowPushFIFO(Graph &g);
    PreflowPushFIFO(const PreflowPushFIFO& orig);
    virtual ~PreflowPushFIFO();
    virtual void exec();
private:
    void examine(int u);
    // "Es gibt eine Liste L, aus der jeweils der erste Knoten abgearbeitet wird"
    vector<int> L; 
};

#endif	/* PREFLOWPUSHFIFO_H */

