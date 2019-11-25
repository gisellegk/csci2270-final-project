#ifndef HASH_HPP
#define HASH_HPP

#include <string>


using namespace std;

struct node
{
    int key;
    struct node* parent;
    struct node* left;
    struct node* right;
};

class HashTableBST
{
    int tableSize;  // No. of buckets (BST)
    int hashFunctionSelect; // which HF to use
    // Pointer to an array containing buckets
    node* *table;

    node* createNode(int key, node* parent);
    int hashFunction(int key);

public:
    HashTableBST(int hashFunctSelect);  // Constructor
    
    // searches for a node
    node* searchBST(node* currNode, int key);
    node* searchItem(int key);
    
    // inserts a key into hash table
    node* insertIntoBST(node* currNode, int key);
    bool insertItem(int key);
    
    // delete a node
    node* deleteFromBST(node* currNode, int key); // blah
    node* deleteItem(int key); // TODO

    // print
    void printTable();
    
    
};

#endif
