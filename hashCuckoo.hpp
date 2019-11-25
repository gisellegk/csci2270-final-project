#ifndef HASHCUCKOO_HPP
#define HASHCUCKOO_HPP

#include <string>
#include "hashFunction.hpp"

using namespace std;

#define EMPTY -1

class HashTableCuckoo
{
    int tableSize;
    int* table0;
    int* table1;

public:
    // Constructor
    HashTableCuckoo();

    // Inserts a key into hash table
    bool insertItem(int key);

    // Function to get the index from the key
    unsigned int hashFunction(int key);

    // Prints the hash table
    void printTable();

    // Searches the hash table for the given key
    int searchItem(int key);

    // Delete the given key from the hash table
    void deleteItem(int key);
};

#endif
