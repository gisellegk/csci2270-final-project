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


/* Private Functions */ 

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


/* Search Functions */ 

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


/* Insert Functions */ 

node* HashTableBST::insertIntoBST(node* currNode, int key){
  // this will either return the new node or nullptr
    if(currNode == nullptr) return nullptr; // just in case.
    if(currNode->key == key) {
      std::cout << "found duplicate" << std::endl;
      return nullptr;
    }
    if(currNode->key > key) { // key is smaller. go left. 
      if(currNode->left) return insertIntoBST(currNode->left, key);
      else {
        // Create Node Here.
        node* newNode = createNode(key);
        currNode->left = newNode;
        return newNode;
      } 
    } else if (currNode->key < key){ // key is larger. go right. 
      if(currNode->right) return insertIntoBST(currNode->right, key);
      else {
        // Create Node Here.
        node* newNode = createNode(key);
        currNode->right = newNode;
        return newNode;
      }
    }
    return nullptr;
    
}

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
    node* newNode = insertIntoBST(bucket, key);
    if(newNode) return true;
    else return false;
  }
}

/* Delete Functions */ 
node* HashTableBST::getMinValueNode(node* currNode){
    if(currNode->left == NULL){
      return currNode;
    }
    return getMinValueNode(currNode->left);
}

node* HashTableBST::deleteItem(int key){
  int index = hashFunction(key);
  node* bucket = table[index];
  return deleteFromBST(bucket, key);
}

node* HashTableBST::deleteFromBST(node *currNode, int value)
{
  if(currNode == NULL) {
    std::cout << "cannot find node to delete." << std::endl;
    return NULL;  
  }
  else if(value < currNode->key) currNode->left = deleteFromBST(currNode->left, value);
  else if(value > currNode->key) currNode->right = deleteFromBST(currNode->right, value);
  else // We found the node with the value
  {
    if(currNode->left == NULL && currNode->right == NULL) { // no child
      delete currNode;
      return NULL;
    }
    else if(currNode->left == NULL) { // only right 
      node* right = currNode->right;
      delete currNode;
      return right;
    }
    else if(currNode->right == NULL) { // only left
      node* left = currNode->left;
      delete currNode;
      return left;
    }
    else { // both l & r
      ///Replace with Minimum from right subtree
      node* minValueNode = getMinValueNode(currNode->right);
      deleteFromBST(currNode, minValueNode->key);
      minValueNode->left = currNode->left;
      minValueNode->right = currNode->right;
      delete currNode;
      return minValueNode;
    }
  }
  return currNode;
}


/* Print Hash Table */
void HashTableBST::printTable()
{
  std::cout<< "Hash Table with BST:" << std::endl;
    for (int i = 0; i < tableSize; i++) {
        std::cout << i << "|| ";
        node* n = table[i];
        if(n) {
          // PRINT BST inorder
          printBST(n);
        } else {
          std::cout << " - " << std::endl;
        }
        cout << endl;
    }
 }

 void HashTableBST::printBST(node* n){
   if(n->left) printBST(n->left);
   std::cout << n->key << " ";
   if(n->right) printBST(n->right);

 }