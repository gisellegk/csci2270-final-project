#ifndef HASH_HPP
#define HASH_HPP

#include <string>


using namespace std;

struct node
{
    int key;
    struct node* left;
    struct node* right;
};

class HashTableBST
{
    int tableSize;  // No. of buckets (BST)
    int hashFunctionSelect; // which HF to use
    // Pointer to an array containing buckets
    node* *table;

    node* createNode(int key);
public:
    HashTableBST(int hashFunctSelect);  // Constructor

    // inserts a key into hash table
    bool insertItem(int key);
    node* insertBST(node* currNode, int key);

    int hashFunction(int key);

    void printTable();

    node* searchItem(int key);
    node* searchBST(node* currNode, int key);
    node* deleteItem(int key); // TODO
};

#endif
