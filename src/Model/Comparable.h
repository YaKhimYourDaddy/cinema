#ifndef COMPARABLE_H
#define COMPARABLE_H

#include <iostream>
using namespace std;

class Comparable {
public:
    virtual ~Comparable() = default;
    virtual bool isMatch(string keyword) = 0; 
};

#endif // COMPARABLE_H