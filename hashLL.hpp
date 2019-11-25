#ifndef HASHLL_HPP
#define HASHLL_HPP

#include <string>

using namespace std;

struct nodeLL
{
    int key;
    struct nodeLL* next;
};

class HashTableLL
{
    int tableSize;

    // Pointer to an array containing LL nodeLLs
    nodeLL* *table;

    // Int determining which hash function to use
    int hashFunctionSelect;
    
    nodeLL* createNode(int key, nodeLL* next);
public:
    // Constructor
    HashTableLL(int hashFunctSelect);

    // Inserts a key into hash table
    bool insertItem(int key);

    // Function to get the index from the key
    unsigned int hashFunction(int key);

    // Prints the hash table
    void printTable();

    // Searches the hash table for the given key
    nodeLL* searchItem(int key);

    // Delete the given key from the hash table
    void deleteItem(int key);
};

#endif
