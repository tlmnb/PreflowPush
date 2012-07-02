/* 
 * File:   PreflowPushRandom.cpp
 * Author: haas
 * 
 * Created on 2. Juli 2012, 16:55
 */

#include "PreflowPushRandom.h"

PreflowPushRandom::PreflowPushRandom(Graph &g): PreflowPushGeneric(&g) {
}

PreflowPushRandom::PreflowPushRandom(const PreflowPushRandom& orig) : PreflowPushGeneric(orig) {
}

PreflowPushRandom::~PreflowPushRandom() {
}

