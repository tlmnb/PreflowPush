/* 
 * File:   Timer.cpp
 * Author: Michael Haas
 *
 * Created on July 9, 2012, 7:04 PM
 */

// Initial version of the timer class downloaded from http://stackoverflow.com/questions/3797708/millisecond-accurate-benchmarking-in-c
// Graciously provided by Stack Overflow user ccSadegh
// License is CC-BY-SA: http://creativecommons.org/licenses/by-sa/3.0/


#include "Timer.h"
#include <cstdlib>


timeval Timer::start() {
    gettimeofday(&this->timer[0], NULL);
    return this->timer[0];
}

timeval Timer::stop() {
    gettimeofday(&this->timer[1], NULL);
    return this->timer[1];
}

int Timer::duration() const {
    int secs(this->timer[1].tv_sec - this->timer[0].tv_sec);
    int usecs(this->timer[1].tv_usec - this->timer[0].tv_usec);

    if (usecs < 0) {
        --secs;
        usecs += 1000000;
    }
    return static_cast<int> (secs * 1000 + usecs / 1000.0 + 0.5);
}
