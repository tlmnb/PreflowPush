/* 
 * File:   PreflowPushExcessScaling.h
 * Author: haas
 *
 * Created on July 3, 2012, 1:53 PM
 */

#ifndef PREFLOWPUSHEXCESSSCALING_H
#define	PREFLOWPUSHEXCESSSCALING_H

#include "PreflowPushGeneric.h"

class PreflowPushExcessScaling : PreflowPushGeneric {
public:
    PreflowPushExcessScaling(Graph &g);
    PreflowPushExcessScaling(const PreflowPushExcessScaling& orig);
    virtual ~PreflowPushExcessScaling();
    virtual void exec();
private:

};

#endif	/* PREFLOWPUSHEXCESSSCALING_H */

