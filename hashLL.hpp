#ifndef HASHLL_HPP
#define HASHLL_HPP

#include <string>
#include "hashFunction.hpp"

using namespace std;

struct node
{
    int key;
    struct node* next;
};

class HashTable
{
    int tableSize;

    // Pointer to an array containing LL nodes
    node* *table;

    // Int determining which hash function to use
    int hashFunctionSelect;
    
    node* createNode(int key, node* next);
public:
    // Constructor
    HashTable(int hashFunctSelect);

    // Inserts a key into hash table
    bool insertItem(int key);

    // Function to get the index from the key
    unsigned int hashFunction(int key);

    // Prints the hash table
    void printTable();

    // Searches the hash table for the given key
    node* searchItem(int key);
};

#endif
