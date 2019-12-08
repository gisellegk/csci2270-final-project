#include <iostream>
#include <iomanip>

#include "hashCuckoo.hpp"
#include "hashFunction.hpp"

//uncomment this for debug prints
// #define DEBUG 1

using namespace std;

nodeCuckoo* HashTableCuckoo::createNode(int key, int table){
    nodeCuckoo* n = new nodeCuckoo();
    n->key = key;
    n->table = table;
    return n;
}

HashTableCuckoo::HashTableCuckoo(){
    this->tableSize= TABLE_SIZE;
    this->numRehashes = 0;
    table0 = new nodeCuckoo*[tableSize];
    table1 = new nodeCuckoo*[tableSize];
    for(int i=0;i<TABLE_SIZE;i++){
        table0[i] = createNode(EMPTY, 0);
        table1[i] = createNode(EMPTY, 1);
    }
}

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
    int index0 = hashFunction0(key, tableSize);
    if(table0[index0]->key != key) {
        int index1 = hashFunction1(key, tableSize);
        if(table1[index1]->key != key) return nullptr; // item not found.
        else return table1[index1]; // found item in table 1
    } else return table0[index0]; // found item in table 0
}

bool HashTableCuckoo::deleteItem(int key){
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
    if(key<0) return true; // no need to insert -1 / empty
    bool insert = insertItemHelper(key);
    while(!insert) {
        #ifdef DEBUG
            std::cout << "failed insert. requires rehash" << std::endl; 
        #endif
        // rehash required. 
        rehash(); // rehash tables
        insert = insertItemHelper(key); // attempt insert again. 
    }
}
// returns true if item is successfully placed. returns false otherwise. 
bool HashTableCuckoo::insertItemHelper(int key){
    nodeCuckoo* n = searchItem(key);
    if(!n){
        // insert the node into table 0
        int index0 = hashFunction0(key, tableSize);
        int index1 = hashFunction1(key, tableSize);
        if(table0[index0]->key == EMPTY) {
            // if the initial spot is empty, put it there.
            table0[index0]->key = key;
            return true;
        } else if (table1[index1]->key == EMPTY) {
            // if the secondary spot is empty, put it there.
            table1[index1]->key = key;
            return true;
        } else {
            // time to move stuff around like the asshole bird namesake 
            nodeCuckoo* moveMe = table0[index0];
            nodeCuckoo* newNode = createNode(key, 0);
            table0[index0] = newNode;
            if(!displace(moveMe, newNode)){
                #ifdef DEBUG
                    std::cout << "item insert failed, try rehashing." << std::endl; 
                #endif
                // needs rehash
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
bool HashTableCuckoo::displace(nodeCuckoo* placeThis, nodeCuckoo* start){
    #ifdef DEBUG
         std::cout << "attempt displacement of " << placeThis->key << std::endl; 
    #endif
    if(placeThis == start) return false;

    // make sure to delete the empty node at the end
    int oldTable = placeThis->table;
    if(oldTable == 0){
        // find spot in table 1. 
        int index = hashFunction1(placeThis->key, tableSize);
        nodeCuckoo* spot = table1[index];

        // put the thing in table 1
        placeThis->table = 1; 
        table1[index] = placeThis;

        // check if the spot was empty, and deal with it 
        if(spot->key != EMPTY) {
            displace(spot, start);
        } else {
            delete spot; // you have to delete this node to prevent a mem leak, because we created a new node to insert at the beginning. 
            return true;
        }

    } else { // oldTable is 1
        // find spot in table 0. 
        int index = hashFunction0(placeThis->key, tableSize);
        nodeCuckoo* spot = table0[index];

        // put the thing in table 0
        placeThis->table = 0; 
        table0[index] = placeThis;

        // check if the spot was empty, and deal with it 
        if(spot->key != EMPTY) {
            displace(spot, start);
        } else {
            delete spot; // you have to delete this node to prevent a mem leak, because we created a new node to insert at the beginning. 
            return true;
        }
    }
}

void HashTableCuckoo::rehash(){
    #ifdef DEBUG
        std::cout << "attempt rehash" << std::endl; 
    #endif
    numRehashes++;
    // increase table size
    int newTableSize = tableSize + 1; // lol idk

    // save old tables
    nodeCuckoo* *old_table0 = table0;
    nodeCuckoo* *old_table1 = table1;
    
    // create 2 new tables
    table0 = new nodeCuckoo*[newTableSize];
    table1 = new nodeCuckoo*[newTableSize];
    for(int i=0; i<newTableSize; i++){
        table0[i] = createNode(EMPTY, 0);
        table1[i] = createNode(EMPTY, 1);
    }
    // insert each item in old tables into new tables
    bool doneCopyingTables = false; 
    int i = 0;

    while(!doneCopyingTables){
        #ifdef DEBUG
            std::cout << "  old_table0 value: " << old_table0[i]->key << std::endl; 
        #endif
        bool tryTable0 = insertItem(old_table0[i]->key);
        #ifdef DEBUG
            std::cout << "  old_table1 value: " << old_table1[i]->key << std::endl; 
        #endif
        bool tryTable1 = insertItem(old_table1[i]->key);

        if(!tryTable0 || !tryTable1){ // if there is ever a failed insert, rehash again. 
            // rehash. Again. :(
            newTableSize++;
            numRehashes++; // does this count as an additional rehash? idk i guess so.
            delete [] table0;
            delete [] table1;
            table0 = new nodeCuckoo*[newTableSize];
            table1 = new nodeCuckoo*[newTableSize];
            for(int i=0; i<newTableSize; i++){
                table0[i] = createNode(EMPTY, 0);
                table1[i] = createNode(EMPTY, 1);
            }
            i = 0; 
        } else {
            i++;
            if(i == tableSize) doneCopyingTables = true;
        }
    }
    tableSize = newTableSize;
}