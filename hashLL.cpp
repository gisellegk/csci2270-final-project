#include <iostream>
#include "hashLL.hpp"

using namespace std;

node* HashTable::createNode(int key, node* next) {
    node* nw = new node;
    nw->key = key;
    nw->next = next;
    return nw;
}

HashTable::HashTable(int hashFunctSelect) {
    this->hashFunctionSelect = hashFunctSelect;
    this->tableSize= TABLE_SIZE;
    table = new node*[tableSize];
    for(int i=0;i<TABLE_SIZE;i++)
        table[i] = nullptr;
}

//Searches the hash table for the given key
node* HashTable::searchItem(int key) {
    //Compute the index by using the hash function
    int index;
    if (hashFunctionSelect) index = hashFunction1(key);
    else index = hashFunction0(key);

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
bool HashTable::insertItem(int key) {
    if(!searchItem(key)) {
        // Use the selected hash function on the key to get the index, then create a LL node with that key
        int index;
        if (hashFunctionSelect) index = hashFunction1(key);
        else index = hashFunction0(key);
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

// Prints the hash table with each LL being a line, with entries separated by ||
void HashTable::printTable() {
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
