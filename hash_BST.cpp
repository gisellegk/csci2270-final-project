// CPP program to implement hashing with chaining
#include <iostream>
#include "hash_BST.hpp"
#include "hashFunction.hpp"

using namespace std;

HashTableBST::HashTableBST(int hashFunctSelect)
{
    this->tableSize= TABLE_SIZE;
    table = new node*[TABLE_SIZE];
    for(int i=0;i<TABLE_SIZE;i++)
        table[i] = nullptr;
    
    hashFunctionSelect = hashFunctSelect;
}

int HashTableBST::hashFunction(int key){
    int index;
    if(hashFunctionSelect) index = hashFunction1(key);
    else index = hashFunction0(key);
    return index;
}

node* HashTableBST::createNode(int key)
{
    node* n = new node;
    n->key = key;
    n->left = nullptr;
    n->right = nullptr;
    return n;
}

node* HashTableBST::searchItem(int key)
{
    //Compute the index by using the hash function
    int index = hashFunction(key);

    if(index < 0) return nullptr;

    //Search the BST at that specific index and return the node if found
    node* bucket = table[index];
    if(bucket){
      // if root of tree exists
      // TODO: traverse BST.
    }
}

//function to insert
bool HashTableBST::insertItem(int key)
{
    node* n = searchItem(key); // see if the bucket exists
    if(!n)
    {
        // Use the hash function on the key to get the index/slot,
        // create a new node with the key and insert it in this slot's list
        int index = hashFunction(key);
        node* newNode = createNode(key);
        table[index] = newNode;

     }
    else {
        node* newNode = createNode(key);
        // TODO: place in BST. 
      
    }
}


// function to display hash table
void HashTableBST::printTable()
{
    for (int i = 0; i < tableSize; i++) {
        cout << i <<"|| ";
        node* n = table[i];
        if(n) {
          cout << n->key << " " ;
          // TODO: PRINT BST
        }
        cout << endl;
    }

 }
