#include <iostream>
#include "hashLL.hpp"

using namespace std;

node* HashTableLL::createNode(int key, node* next) {
    node* nw = new node;
    nw->key = key;
    nw->next = next;
    return nw;
}

HashTableLL::HashTableLL(int hashFunctSelect) {
    this->hashFunctionSelect = hashFunctSelect;
    this->tableSize= TABLE_SIZE;
    table = new node*[tableSize];
    for(int i=0;i<TABLE_SIZE;i++)
        table[i] = nullptr;
}

//Searches the hash table for the given key
node* HashTableLL::searchItem(int key) {
    //Compute the index by using the hash function
    int index = hashFunction(key);

    //Search the list at that specific index and return the node if found
    node* n = table[index];
    while (n != nullptr) {
        if (n->key == key) {
            return n;
        }
        n = n->next;
    }
}

//Inserts the given key to the proper place in the hash table
bool HashTableLL::insertItem(int key) {
    if(!searchItem(key)) {
        // Use the selected hash function on the key to get the index, then create a LL node with that key
        int index = hashFunction(key);
        node* newNode = new node();
        newNode->key = key;

        // Put the new node at the front of the LL in the table
        node* node = table[index];
        newNode->next = node;
        table[index] = newNode;
        return true;
    } else {
        cout<<"duplicate entry: "<<key<<endl;
        return false;
    }
}

unsigned int HashTableLL::hashFunction(int key) {
    if (hashFunctionSelect)
        return hashFunction1(key);
    else
        return hashFunction0(key);
}

// Prints the hash table with each LL being a line, with entries separated by ||
void HashTableLL::printTable() {
    for (int i = 0; i < tableSize; i++) {
        cout << i <<"|| ";

        node* n = table[i];
        while (n != nullptr) {
            cout << n->key << " ";
            n = n->next;
        }
        cout << endl;
    }
 }

// Deletes the given key from the hash table
 void HashTableLL::deleteItem(int key) {
    //Compute the index by using the hash function
    int index = hashFunction(key);

    //Search the list at that specific index and delete the node if found
    node* n = table[index];
    node* prev = nullptr;
    while (n != nullptr) {
        if (n->key == key) {

            // Check if the node is at the start of the LL
            if (prev == nullptr) {
                table[index] = n->next;
                delete n;
                return;
            }
            
            prev->next = n->next;
            delete n;
            return;
        }
        prev = n;
        n = n->next;
    }
 }
