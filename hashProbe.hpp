#ifndef HASHLL_HPP
#define HASHLL_HPP

#include <string>
#include "hashFunction.hpp"

using namespace std;

// Constants for empty/deleted elements in the hash table
#define DELETED -2
#define EMPTY -1

class HashTableProbe
{
    int tableSize;

    // An array of integers
    int* table;

    // Int determining which hash function to use
    int hashFunctionSelect;
public:
    // Constructor
    HashTableProbe(int hashFunctSelect);

    // Inserts a key into hash table
    bool insertItem(int key);

    // Function to get the index from the key
    unsigned int hashFunction(int key);

    // Prints the hash table
    void printTable();

    // Searches the hash table for the given key
    int searchItem(int key);

    // Deletes the given key from the hash table
    void deleteItem(int key);
};

#endif