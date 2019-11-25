#ifndef HASHFUNCTION_HPP
#define HASHFUNCTION_HPP

#include <math.h>

#define TABLE_SIZE 10009

unsigned int hashFunction0(int key) {
    return key % TABLE_SIZE;
}

unsigned int hashFunction1(int key) {
    return floor(key / TABLE_SIZE);
}

#endif