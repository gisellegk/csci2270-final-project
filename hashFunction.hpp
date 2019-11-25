#ifndef HASHFUNCTION_HPP
#define HASHFUNCTION_HPP

#include <math.h>

#define TABLE_SIZE 10009
// Constants for empty/deleted elements in the hash table
#define DELETED -2
#define EMPTY -1

unsigned int hashFunction0(int key);

unsigned int hashFunction1(int key);

#endif