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

node* HashTableBST::searchBST(node* currNode, int key){
    if(currNode == nullptr) return nullptr;

    if(currNode->key == key) return currNode;

    if(currNode->key > key) return searchBST(currNode->left, key);

    return searchBST(currNode->right, key);
}

node* HashTableBST::searchItem(int key)
{
    //Compute the index by using the hash function
    int index = hashFunction(key);

    if(index < 0) return nullptr;

    //Search the BST at that specific index and return the node if found
    node* n = table[index]; // get bucket
    if(n){
      // if root of tree exists
      n = searchBST(n, key); // search for key where bucket = root.
    }
}

// this will either return the new node or nullptr
node* HashTableBST::insertBST(node* currNode, int key){
    if(currNode == nullptr) return nullptr; // just in case.
    if(currNode->key == key) {
      std::cout << "found duplicate" << std::endl;
      return nullptr;
    }
    if(currNode->key > key) { // key is smaller. go left. 
      if(currNode->left) return insertBST(currNode->left, key);
      else {
        // Create Node Here.
        node* newNode = createNode(key);
        currNode->left = newNode;
        return newNode;
      } 
    } else if (currNode->key < key){ // key is larger. go right. 
      if(currNode->right) return insertBST(currNode->right, key);
      else {
        // Create Node Here.
        node* newNode = createNode(key);
        currNode->right = newNode;
        return newNode;
      }
    }
    return nullptr;
    
}

//function to insert
bool HashTableBST::insertItem(int key)
{
  // find bucket.
  int index = hashFunction(key);
  node* bucket = table[index];

  if(!bucket){ // if bucket does not exist
    node* newNode = createNode(key);
    table[index] = newNode;
    return true;
  } else { // traverse BST. 
    node* newNode = insertBST(bucket, key);
    if(newNode) return true;
    else return false;
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
