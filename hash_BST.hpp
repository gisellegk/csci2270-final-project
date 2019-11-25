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

    // Pointer to an array containing buckets
    node* *table;

    node* createNode(int key, node* next);
public:
    HashTableBST(int bsize, int func);  // Constructor

    // inserts a key into hash table
    bool insertItem(int key);

    void printTable();

    node* searchItem(int key);
};

#endif
