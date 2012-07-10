/* 
 * File:   PreflowPushRandom.cpp
 * Author: Michael Haas
 * 
 * Implements the Random strategy for the PreflowPush algorithm.
 * For more details, see @PreflowPushRandom::exec().
 * 
 * Created on 2. Juli 2012, 16:55
 */

#include "PreflowPushRandom.h"

/**
 * Constructor.
 * See superclass for documentation.
 * 
 * @param g
 */
PreflowPushRandom::PreflowPushRandom(Graph* g) : PreflowPushGeneric(g) {
}

/**
 * Constructor.
 * 
 * See superclass for documentation.
 * @param orig
 */
PreflowPushRandom::PreflowPushRandom(const PreflowPushRandom& orig) : PreflowPushGeneric(orig) {
}

/**
 * The Random strategy applies any applicable Push or Lift operation
 * until no further operations can be applied. The algorithm is then finished.
 * 
 */
void PreflowPushRandom::exec() {
    // " Solange eine anwendbare Push- oder Lift-Operation existiert, führe eine solche aus.
    bool changed = false;
    do {
        changed = false;
        int a = this->h.size();
        for (int uu = 0; uu < a; uu++) {
            changed = (this->lift(uu) || changed);
            for (int vv = 0; vv < a; vv++) {
                changed = (this->push(uu, vv) || changed);
            }
        }
    } while (changed);
}

PreflowPushRandom::~PreflowPushRandom() {
}

