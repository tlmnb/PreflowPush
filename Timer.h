/* 
 * File:   Timer.h
 * Author: Michael Haas
 *
 * Created on July 9, 2012, 7:04 PM
 */


// Initial version of the timer class downloaded from http://stackoverflow.com/questions/3797708/millisecond-accurate-benchmarking-in-c
// Graciously provided by Stack Overflow user ccSadegh
// License is CC-BY-SA: http://creativecommons.org/licenses/by-sa/3.0/

#ifndef TIMER_H
#define	TIMER_H

#include <sys/time.h>

class Timer{
private:
     timeval timer[2];
public:
    timeval start();
    timeval stop();
    int duration() const;
};


#endif	/* TIMER_H */

