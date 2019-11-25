#include <iostream>
#include "hashProbe.hpp"

using namespace std;

// Constructor
HashTableProbe::HashTableProbe(int hashFunctSelect) {
    this->hashFunctionSelect = hashFunctSelect;
    this->tableSize= TABLE_SIZE;
    table = new int[tableSize];
    // Initialize every element in the table to empty
    for(int i=0;i<TABLE_SIZE;i++)
        table[i] = EMPTY;
}

// Inserts a key into hash table
bool HashTableProbe::insertItem(int key) {
    int index = hashFunction(key);

    // Case 0: the index given is taken by the key we're inserting
    if (table[index] == key) {
        cout << "duplicate entry: " << key << endl;
        return false;
    }

    // Case 1: the index given by the hash function is available -> insert the key there
    if (table[index] == EMPTY || table[index] == DELETED) {
        table[index] = key;
        return true;
    }

    // If the element at index isn't available we have to do linear probing to find the next available one
    while (table[index] != EMPTY || table[index] != DELETED) {
        // Check if the key has been entered already
        if (table[index] == key) {
            cout << "duplicate entry: " << key << endl;
            return false;
        }

        // Loop back around at the end of the table
        if (index == TABLE_SIZE-1)
            index = 0;
        else
            // Move to the next element in the table
            index++;
    }
    
    // The next open spot has been found, and it's not a duplicate key
    table[index] = key;
    return true;
}

// Function to get the index from the key
unsigned int HashTableProbe::hashFunction(int key) {
    if (hashFunctionSelect)
        return hashFunction1(key);
    else
        return hashFunction0(key);
}

// Prints the hash table with spaces for empty elements and 'x' for deleted ones, with 100 elements on a line
void HashTableProbe::printTable() {
    int lineCount = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << " " << i << " : ";
        if (table[i] == EMPTY) cout << " ";
        else if (table[i] == DELETED) cout << "x";
        else cout << table[i];
        cout << " |";

        if (lineCount == 99) {
            cout << endl;
            lineCount = 0;
        }
        lineCount++;
    }
}

// Searches the hash table for the given key, returns -1 if key not found
int HashTableProbe::searchItem(int key) {
    // Get the index from the hash function as a starting place for the search
    int index = hashFunction(key);

    // Case 1: the key is at the given index, no probing required
    if (table[index] == key) {
        return index;
    }

    // Otherwise need to linear probe with a step size of 1 until we reach the key, or an EMPTY element
    while (table[index] != EMPTY) {
        // Check if the new location has the key
        if (table[index] == key) {
            return index;
        }

        // Check to loop back to the start of the table
        if (index == TABLE_SIZE-1)
            index = 0;
        else
            index++;
    }

    // Key wasn't found, return -1 for failure
    return -1;
}

// Deletes the given key from the hash table
void HashTableProbe::deleteItem(int key) {
    // Get the index from the hash function as a starting place for the search
    int index = hashFunction(key);

    // Case 1: the key is at the given index, no probing required
    if (table[index] == key) {
        table[index] = DELETED;
        return;
    }

    // Otherwise need to linear probe with a step size of 1 until we reach the key, or an EMPTY element
    while (table[index] != EMPTY) {
        // Check if the new location has the key
        if (table[index] == key) {
            table[index] = DELETED;
            return;
        }

        // Check to loop back to the start of the table
        if (index == TABLE_SIZE-1)
            index = 0;
        else
            index++;
    }
}