/* 
 * File:   PreflowPushRandom.cpp
 * Author: haas
 * 
 * Created on 2. Juli 2012, 16:55
 */

#include "PreflowPushRandom.h"

PreflowPushRandom::PreflowPushRandom(Graph* g) : PreflowPushGeneric(g) {
}

PreflowPushRandom::PreflowPushRandom(const PreflowPushRandom& orig) : PreflowPushGeneric(orig) {
}

void PreflowPushRandom::exec() {
    // in the script, this is not really random, it's just 
    // " Solange eine anwendbare Push- oder Lift-Operation existiert, f¨ hre eine solche aus.
    // thus, we don't need proper randomness
    // we could iterate over all nodes, but that seems like a waste of time
    // can we restrict the selection of (u,v) or (u)?
    bool changed = false;
    do {
        std::cerr << "Loop" << std::endl;
        this->print();
        changed = false;
        int a = this->h.size();
        for (int uu = 0; uu < a; uu++) {
            // this should only work if lift is an applicable operation
            bool res = this->lift(uu);
            if (res)
                std::cerr << "Lift(" << uu << ")  successful" << std::endl;
            changed = (res || changed);
            for (int vv = 0; vv < a; vv++) {
                // this should only work if push is an applicable operation
                bool pushRes = this->push(uu, vv);
                if (pushRes)
                    std::cerr << "Push(" << uu << "," << vv << ") successful." << std::endl;
                changed = (pushRes || changed);
            }
        }
    } while (changed);
}

PreflowPushRandom::~PreflowPushRandom() {
}

