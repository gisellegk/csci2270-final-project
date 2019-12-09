#include <iostream>
#include <iomanip>

#include "hashCuckoo.hpp"
#include "hashFunction.hpp"
#include "primes.hpp"

// Uncomment this for debug prints
// #define DEBUG 1

using namespace std;

nodeCuckoo* HashTableCuckoo::createNode(int key, int table){
    nodeCuckoo* n = new nodeCuckoo();
    n->key = key;
    n->table = table;
    return n;
}

HashTableCuckoo::HashTableCuckoo(){
    #ifdef DEBUG
        std::cout << "make new tables" << std::endl; 
    #endif
    this->tableSize= TABLE_SIZE;
    this->numRehashes = 0;
    table0 = new nodeCuckoo*[tableSize];
    table1 = new nodeCuckoo*[tableSize];
    // Fill the hash table with empty nodes
    for(int i=0;i<TABLE_SIZE;i++){
        table0[i] = createNode(EMPTY, 0);
        table1[i] = createNode(EMPTY, 1);
    }
}

// New constructor only used in cuckootest.cpp
HashTableCuckoo::HashTableCuckoo(int size){
    #ifdef DEBUG
        std::cout << "make new tables" << std::endl; 
    #endif
    this->tableSize= size;
    this->numRehashes = 0;
    table0 = new nodeCuckoo*[tableSize];
    table1 = new nodeCuckoo*[tableSize];
    for(int i=0;i<size;i++){
        #ifdef DEBUG
            std::cout << i << std::endl;
        #endif
        table0[i] = createNode(EMPTY, 0);
        table1[i] = createNode(EMPTY, 1);
    }
}

nodeCuckoo* HashTableCuckoo::searchItem(int key){
    // Get the index of table0 for the key
    int index0 = hashFunction0(key, tableSize);
    if(table0[index0]->key != key) {
        // If table0 doesn't have the key look in table1
        int index1 = hashFunction1(key, tableSize);
        if(table1[index1]->key != key) return nullptr; // item not found.
        else return table1[index1]; // found item in table 1
    } else return table0[index0]; // found item in table 0
}

bool HashTableCuckoo::deleteItem(int key){
    // Search for the key before deleting
    nodeCuckoo* n = searchItem(key);
    if(!n) return false; // item not found. Could not delete.
    else {
        n->key = EMPTY;
        return true;
    }
}

void HashTableCuckoo::printTables(){
    std::cout << "TABLE 0" << std::endl;
    for(int i = 0; i < tableSize; i++) {
        if (table0[i]->key == -1);
        else
        std::cout << std::setw(6) << i << " | " << std::setw(6) << table0[i]->key << std::endl;
    }
    std::cout << "TABLE 1" << std::endl;
    for(int i = 0; i < tableSize; i++) {
        if (table1[i]->key == -1);
        else
        std::cout << std::setw(6) << i << " | " << std::setw(6) << table1[i]->key << std::endl;
    }
}

bool HashTableCuckoo::insertItem(int key){
    if(key<0) return true; // no need to insert -1 / empty nodes
    bool insert = insertItemHelper(key, tableSize);
    // If the insert fails, check for cycles and rehashing
    while(!insert) {
        #ifdef DEBUG
            std::cout << "failed insert. requires rehash" << std::endl; 
        #endif
        // rehash required, might need multiple rehashes, wait for reshash to return a success
        bool rehashSuccess = false;
        while (!rehashSuccess) {
            rehashSuccess = rehash();
        }
        // cout << "finished rehashing, table is now " << tableSize << endl;
        // cout << "trying to insert " << key << " again" << endl;
        insert = insertItemHelper(key, tableSize); // attempt insert again.
        // cout << "insert: " << insert << endl;
    }
    return insert;
}
// returns true if item is successfully placed. returns false otherwise. 
bool HashTableCuckoo::insertItemHelper(int key, int newTableSize){
    if(key<0) return true; // no need to insert -1 / empty
    nodeCuckoo* n = searchItem(key);
    // Only try to insert if the key isn't already existing
    if(!n){
        // Insert the node into table 0
        int index0 = hashFunction0(key, newTableSize);
        int index1 = hashFunction1(key, newTableSize);
        if(table0[index0]->key == EMPTY) {
            // if the initial spot is empty, put it there.
            table0[index0]->key = key;
            return true;
        } else if (table1[index1]->key == EMPTY) {
            // if the secondary spot is empty, put it there.
            table1[index1]->key = key;
            return true;
        } else {
            // time to move stuff around because of collision
            // Create a temp node for the old value
            nodeCuckoo* oldNode = table0[index0];
            nodeCuckoo* newNode = createNode(key, 0);
            table0[index0] = newNode;
            // Do recursive displacement of nodes, false is returned if a cycle is detected
            if(!displace(oldNode, newNode, newTableSize)){
                #ifdef DEBUG
                    std::cout << "item insert failed, try rehashing." << std::endl; 
                #endif
                // needs rehash
                // cout << "cycle detected with node " << newNode->key << " and " << oldNode->key << endl;
                table0[index0] = oldNode;
                return false;
            } else return true;
        }
    } else {
        // this is a duplicate, ignore it
        std::cout << "ignoring duplicate of " << key << std::endl;
        return true;
    }
}

// returns true if item is successfully placed. Returns false if a loop is detected.
bool HashTableCuckoo::displace(nodeCuckoo* placeThis, nodeCuckoo* startNode, int newTableSize){
    #ifdef DEBUG
         std::cout << "attempt displacement of " << placeThis->key << std::endl; 
    #endif
    // Base case, if the node that started this displacement chain is displaced return false (cycle detected)
    if(placeThis == startNode) return false;

    // If the node being displaced was in table0 put in in table1, if it was in table1 put it in table0
    int oldTable = placeThis->table;
    if(oldTable == 0){
        // find spot in table 1. 
        int index = hashFunction1(placeThis->key, newTableSize);
        nodeCuckoo* spot = table1[index];

        // put the thing in table 1
        placeThis->table = 1; 
        table1[index] = placeThis;

        // check if the spot was empty, and deal with it 
        if(spot->key != EMPTY) {
            return displace(spot, startNode, newTableSize);
        } else {
            delete spot; // you have to delete this node to prevent a mem leak, because we created a new node to insert at the beginning. 
            return true;
        }

    } else { // oldTable is 1
        // find spot in table 0. 
        int index = hashFunction0(placeThis->key, newTableSize);
        nodeCuckoo* spot = table0[index];

        // put the thing in table 0
        placeThis->table = 0; 
        table0[index] = placeThis;

        // check if the spot was empty, and deal with it 
        if(spot->key != EMPTY) {
            return displace(spot, startNode, newTableSize);
        } else {
            delete spot; // you have to delete this node to prevent a mem leak, because we created a new node to insert at the beginning. 
            return true;
        }
    }
}

bool HashTableCuckoo::rehash(){
    #ifdef DEBUG
        // std::cout << "attempt rehash " << numRehashes << std::endl; 
    #endif
    numRehashes++;
    // increase table size
    int newTableSize = primes[numRehashes];
    // cout << "new table size = " << newTableSize << endl;
    // save old tables
    nodeCuckoo* *old_table0 = table0;
    nodeCuckoo* *old_table1 = table1;
    
    // create 2 new tables & fill them with empty values
    table0 = new nodeCuckoo*[newTableSize];
    table1 = new nodeCuckoo*[newTableSize];
    for(int i=0; i<newTableSize; i++){
        table0[i] = createNode(EMPTY, 0);
        table1[i] = createNode(EMPTY, 1);
    }
    // insert each item in old tables into new tables
    for (int i=0; i < tableSize; i++) {
        // Insert and if it fails, return false and new rehash needed
        // Reinsert value from old table0
        if (!insertItemHelper(old_table0[i]->key, newTableSize)) {
            // Delete the failed rehashed table
            for (int i = 0; i < newTableSize; i++) {
                delete table0[i];
                delete table1[i];
            }
            delete [] table0;
            delete [] table1;
            table0 = old_table0;
            table1 = old_table1;
            return false;
        }

        // Reinsert key from table1 to new table
        if (!insertItemHelper(old_table1[i]->key, newTableSize)) {
            // Delete the failed rehashed table
            for (int i = 0; i < newTableSize; i++) {
                delete table0[i];
                delete table1[i];
            }
            delete [] table0;
            delete [] table1;
            table0 = old_table0;
            table1 = old_table1;
            return false;
        }
    }
    
    // cout << "rehash complete" << endl;
    tableSize = newTableSize;
    delete [] old_table0;
    delete [] old_table1;
    return true;
}

int HashTableCuckoo::getNumRehashes() {
    return numRehashes;
}