#include <iostream>
#include <iomanip>
#include "hashLL.hpp"
#include "hashFunction.hpp"

using namespace std;

nodeLL* HashTableLL::createNode(int key, nodeLL* next) {
    nodeLL* nw = new nodeLL;
    nw->key = key;
    nw->next = next;
    return nw;
}

HashTableLL::HashTableLL(int hashFunctSelect) {
    this->hashFunctionSelect = hashFunctSelect;
    this->tableSize= TABLE_SIZE;
    table = new nodeLL*[tableSize];
    for(int i=0;i<TABLE_SIZE;i++)
        table[i] = nullptr;
}

//Searches the hash table for the given key
nodeLL* HashTableLL::searchItem(int key) {
    //Compute the index by using the hash function
    int index = hashFunction(key);

    //Search the list at that specific index and return the nodeLL if found
    nodeLL* n = table[index];
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
        // Use the selected hash function on the key to get the index, then create a LL nodeLL with that key
        int index = hashFunction(key);
        nodeLL* newNode = new nodeLL();
        newNode->key = key;

        // Put the new node at the front of the LL in the table
        nodeLL* node = table[index];
        newNode->next = node;
        table[index] = newNode;
        return true;
    } else {
        //cout<<"duplicate entry: "<<key<<endl;
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
        cout << setw(6) << i <<"|| ";

        nodeLL* n = table[i];
        while (n != nullptr) {
            cout << setw(6) << n->key << " ";
            n = n->next;
        }
        cout << endl;
    }
 }

// Deletes the given key from the hash table
 void HashTableLL::deleteItem(int key) {
    //Compute the index by using the hash function
    int index = hashFunction(key);

    //Search the list at that specific index and delete the nodeLL if found
    nodeLL* n = table[index];
    nodeLL* prev = nullptr;
    while (n != nullptr) {
        if (n->key == key) {

            // Check if the nodeLL is at the start of the LL
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
