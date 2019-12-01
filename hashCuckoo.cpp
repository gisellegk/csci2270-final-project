#include <iostream>
#include <iomanip>

#include "hashCuckoo.hpp"
#include "hashFunction.hpp"

using namespace std;

nodeCuckoo* HashTableCuckoo::createNode(int key, int table){
    nodeCuckoo* n = new nodeCuckoo();
    n->key = key;
    n->table = table;
    n->duplicates = 0;
    return n;
}

HashTableCuckoo::HashTableCuckoo(){
    this->tableSize= TABLE_SIZE;
    table0 = new nodeCuckoo*[tableSize];
    table1 = new nodeCuckoo*[tableSize];
    for(int i=0;i<TABLE_SIZE;i++){
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
        n->duplicates = 0;
        return true;
    }
}

void HashTableCuckoo::printTables(){
    std::cout << "TABLE 0" << std::endl;
    for(int i = 0; i < tableSize; i++) {
        std::cout << std::setw(6) << i << " | " << std::setw(6) << table0[i] << std::endl;
    }
    std::cout << "TABLE 1" << std::endl;
    for(int i = 0; i < tableSize; i++) {
        std::cout << std::setw(6) << i << " | " << std::setw(6) << table1[i] << std::endl;
    }
}

bool HashTableCuckoo::insertItem(int key){
    bool insert = insertItemHelper(key);
    while(!insert) {
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
                // needs rehash
                return false;
            } else return true;
        }
    } else {
        // this is a duplicate
        n->duplicates++;
        return true;
    }
}

// returns true if item is successfully placed. Returns false if a loop is detected.
bool HashTableCuckoo::displace(nodeCuckoo* placeThis, nodeCuckoo* start){
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
    // increase table size
    // create 2 new tables
    // insert each item in old tables into new tables
    // if there is ever a failed insert, rehash again. 

}