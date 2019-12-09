#include "hashFunction.hpp"

unsigned int hashFunction0(int key) {
    return key % TABLE_SIZE;
}

unsigned int hashFunction1(int key) {
    return floor(key / TABLE_SIZE);
}

// Used in cuckoo hashing
unsigned int hashFunction0(int key, int size) {
    return key % size;
}

// Used in cuckoo hashing
unsigned int hashFunction1(int key, int size) {
    int floored = floor(key /size);
    return floored % size;
}