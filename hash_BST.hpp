#ifndef HASH_HPP
#define HASH_HPP

#include <string>


using namespace std;

struct nodeBST
{
    int key;
    struct nodeBST* left;
    struct nodeBST* right;
};

class HashTableBST
{
    int tableSize;  // No. of buckets (BST)
    int hashFunctionSelect; // which HF to use
    // Pointer to an array containing buckets
    nodeBST* *table;

    nodeBST* createNode(int key);
    int hashFunction(int key);

public:
    HashTableBST(int hashFunctSelect);  // Constructor
    
    // searches for a node
    nodeBST* searchBST(nodeBST* currNode, int key);
    nodeBST* searchItem(int key);
    
    // inserts a key into hash table
    nodeBST* insertIntoBST(nodeBST* currNode, int key);
    bool insertItem(int key);
    
    // delete a node
    nodeBST* getMinValueNode(nodeBST* currNode);
    nodeBST* deleteFromBST(nodeBST* currNode, int key); // blah
    nodeBST* deleteItem(int key); // TODO

    // print
    void printTable();
    void printBST(nodeBST* n);
    
    
};

#endif
