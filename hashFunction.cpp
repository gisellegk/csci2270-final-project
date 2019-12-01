#include "hashFunction.hpp"

unsigned int hashFunction0(int key) {
    return key % TABLE_SIZE;
}

unsigned int hashFunction1(int key) {
    return floor(key / TABLE_SIZE);
}

unsigned int hashFunction0(int key, int size) {
    return key % size;
}

unsigned int hashFunction1(int key, int size) {
    int floored = floor(key /size);
    return floored % size;
}