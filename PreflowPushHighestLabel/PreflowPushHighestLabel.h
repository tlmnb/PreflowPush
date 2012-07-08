/* 
 * File:   PreflowPushHighestLabel.h
 * Author: haas
 *
 * Created on July 3, 2012, 1:52 PM
 */

#ifndef PREFLOWPUSHHIGHESTLABEL_H
#define	PREFLOWPUSHHIGHESTLABEL_H

#include "../PreflowPushGeneric.h"

class PreflowPushHighestLabel : public PreflowPushGeneric {
public:
    PreflowPushHighestLabel(Graph* g);
    PreflowPushHighestLabel(const PreflowPushHighestLabel& orig);
    virtual ~PreflowPushHighestLabel();
    virtual void exec();
private:
    class Comperator {
        public:
            Comperator(PreflowPushHighestLabel* phl);
            bool operator()(const int& a, const int& b);
            PreflowPushGeneric* phl; 
        private:
            
    };
};

#endif	/* PREFLOWPUSHHIGHESTLABEL_H */

