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

node* HashTableBST::createNode(int key, node* parent)
{
    node* n = new node;
    n->key = key;
    n->parent = parent;
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
        node* newNode = createNode(key, currNode);
        currNode->left = newNode;
        return newNode;
      } 
    } else if (currNode->key < key){ // key is larger. go right. 
      if(currNode->right) return insertIntoBST(currNode->right, key);
      else {
        // Create Node Here.
        node* newNode = createNode(key, currNode);
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
    node* newNode = createNode(key, nullptr);
    table[index] = newNode;
    return true;
  } else { // traverse BST. 
    node* newNode = insertIntoBST(bucket, key);
    if(newNode) return true;
    else return false;
  }
}

/* Delete Functions */ 
node* HashTableBST::deleteFromBST(node* currNode, int key){

}
node* HashTableBST::deleteItem(int key){


}


/* Print Hash Table */
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

Node* BST::getMaxValueNode(Node* currNode){
    if(currNode->right == NULL){
        return currNode;
    }
    return getMaxValueNode(currNode->right);
}

Node* BST::getMinValueNode(Node* currNode){

    if(currNode->left == NULL){
      return currNode;
    }
    return getMinValueNode(currNode->left);
}


//--------------------------- Delete a Node ------------------------------------------------

// This function deletes the Node with 'value' as it's key. This is to be called inside removeRange() function
// SILVER TODO Complete the implementation of this function
Node* BST::deleteNode(Node *currNode, int value)
{

  if(currNode == NULL)
  {
    return NULL;
  }
  else if(value < currNode->key)
  {
    currNode->left = deleteNode(currNode->left, value);
  }
  else if(value > currNode->key)
  {
    currNode->right = deleteNode(currNode->right, value);
  }
  // We found the node with the value
  else
  {
    //TODO Case : No child
    if(currNode->left == NULL && currNode->right == NULL)
    {
        return NULL;
    }
    //TODO Case : Only right child
    else if(currNode->left == NULL)
    {
        return currNode->right;
    }
    //TODO Case : Only left child
    else if(currNode->right == NULL)
    {
        return currNode->left;
    }
    //TODO Case: Both left and right child
    else
    {
      ///Replace with Minimum from right subtree
      Node* minValueNode = getMinValueNode(currNode->right);
      deleteNode(currNode, minValueNode->key);
      minValueNode->left = currNode->left;
      minValueNode->right = currNode->right;
      return minValueNode;
    }

  }
return currNode;
}