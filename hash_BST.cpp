// CPP program to implement hashing with chaining
#include <iostream>
#include "hash_BST.hpp"


using namespace std;

HashTableBST::HashTableBST(int bsize, int funct)
{
    this->tableSize= bsize;
    table = new node*[tableSize];
    for(int i=0;i<bsize;i++)
        table[i] = nullptr;
}

node* HashTableBST::createNode(int key, node* next)
{
    node* nw = new node;
    nw->key = key;
    nw->next = next;
    return nw;
}

// TODO Complete this function
//function to search
node* HashTableBST::searchItem(int key)
{
    //Compute the index by using the hash function
    int index = hashFunction(key);
    if(index < 0) return nullptr;

    //TODO: Search the list at that specific index and return the node if found
    return table[index];
}

//TODO Complete this function
//function to insert
bool HashTableBST::insertItem(int key)
{
    node* n = searchItem(key);
    if(!n)
    {
        // TODO :
        // Use the hash function on the key to get the index/slot,
        // create a new node with the key and insert it in this slot's list
        int index = hashFunction(key);
        node* newNode = new node();
        newNode->key = key;
        table[index] = newNode;

     }
    else{
      if(n->key == key){
        cout<<"duplicate entry: "<<key<<endl;
        return false;
      } else {
        node* newNode = new node();
        newNode->key = key;
        while(n->next){
          n = n->next;
        }
        n->next = newNode;
      }
    }

}

//TODO Complete this function
// function to display hash table
void HashTableBST::printTable()
{
    for (int i = 0; i < tableSize; i++) {
        cout << i <<"|| ";
        node* n = table[i];
        if(n) {
          cout << n->key << " " ;
          while(n->next){
            n=n->next;
            cout << n->key << " " ;
          }
        }
        cout << endl;

        //TODO
    }

 }
