#include <iostream>
#include "hashCuckoo.hpp"
#include "hashFunction.hpp"

using namespace std;

HashTableCuckoo::HashTableCuckoo(){
    this->tableSize= TABLE_SIZE;
    table0 = new int[tableSize];
    table1 = new int[tableSize];
    for(int i=0;i<TABLE_SIZE;i++){
        table0[i] = EMPTY;
        table1[i] = EMPTY;
    }
}

bool HashTableCuckoo::insertItem(int key){
    int index0 = hashFunction0(key);
    if(table0[index0] != EMPTY) {
        int index1 = hashFunction1(key);
        if(table)
    }

}