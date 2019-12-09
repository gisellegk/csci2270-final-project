#ifndef HASHCUCKOO_HPP
#define HASHCUCKOO_HPP

#include <string>
#include "hashFunction.hpp"

using namespace std;

struct nodeCuckoo
{
    int key;
    int table;
};

class HashTableCuckoo
{
    int tableSize;
    int numRehashes; 
    nodeCuckoo* *table0;
    nodeCuckoo* *table1;
    nodeCuckoo* createNode(int key, int table);

public:
    // Constructor
    HashTableCuckoo();
    HashTableCuckoo(int size);

    // Searches the hash table for the given key
    nodeCuckoo* searchItem(int key);

    // Delete the given key from the hash table
    bool deleteItem(int key);
    
    // Prints the hash tables
    void printTables();

    // Inserts a key into hash table
    bool insertItem(int key);
    bool insertItemHelper(int key, int newTableSize);
    bool displace(nodeCuckoo* placeThis, nodeCuckoo* start, int newTableSize);
    bool rehash(); 

    int getNumRehashes();

};

#endif
