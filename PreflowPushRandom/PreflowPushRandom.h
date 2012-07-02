/* 
 * File:   PreflowPushRandom.h
 * Author: haas
 *
 * Created on 2. Juli 2012, 16:55
 */



#ifndef PREFLOWPUSHRANDOM_H
#define	PREFLOWPUSHRANDOM_H

#include "PreflowPushGeneric.h"

class PreflowPushRandom : public PreflowPushGeneric {
public:
    PreflowPushRandom(Graph &g);
    PreflowPushRandom(const PreflowPushRandom& orig);
    virtual ~PreflowPushRandom();
private:

};

#endif	/* PREFLOWPUSHRANDOM_H */

