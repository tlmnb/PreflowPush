/* 
 * File:   ProblemTest.h
 * Author: haas
 *
 * Created on 2. Juli 2012, 14:48
 */

#include <cstdlib>
#include <vector>
#include <string>

#ifndef PROBLEMTEST_H
#define	PROBLEMTEST_H

using namespace std;

class ProblemTest {
private:
    const static int COUNT = 9;
    vector<int> results;
    void test(string file, int desiredFlow);
    void testAll();
public:
    ProblemTest() {};
    int run();
};


#endif	/* PROBLEMTEST_H */

