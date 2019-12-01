// g++ -std=c++11 cuckootest.cpp hashCuckoo.hpp hashCuckoo.cpp hashFunction.cpp hashFunction.hpp

#include <iostream>
#include "hashCuckoo.hpp"
#include "hashFunction.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
    cout << "initiating test" << endl;
    HashTableCuckoo* cuckoo = new HashTableCuckoo(3);
    cout << "created hash table" << endl;
    cuckoo->printTables(); 
    cout << "expected empty table" << endl << endl;
    // items to insert
    // 1 % 3 = 1
    cout << "insert key: 1" << endl;
    cuckoo->insertItem(1);
    cuckoo->printTables();
    cout << "expected: table 0: [-1 1 -1] table 1: [-1 -1 -1]" << endl << endl;
    // 10 % 3 = 1, floor(10/3) = 3, 3%3 = 0 (one collision)
    cout << "insert key: 10" << endl;
    cuckoo->insertItem(10);
    cuckoo->printTables();
    cout << "expected: table 0: [-1 1 -1] table 1: [10 -1 -1]" << endl << endl;
    // 4 % 3 = 1, floor(4/3) = 1
    cout << "insert key: 4" << endl;
    cuckoo->insertItem(4);
    cuckoo->printTables();
    cout << "expected:  table 0: [-1 1 -1] table 1: [10 4 -1]" << endl << endl;
    // 0 % 3 = 0
    cout << "insert key: 0" << endl;
    cuckoo->insertItem(0);
    cuckoo->printTables();
    cout << "expected:  table 0: [0 1 -1] table 1: [10 4 -1]" << endl << endl;
    // 12 % 3 = 0, floor(12/3) = 4, 4%3 = 1
    cout << "insert key: 12" << endl;
    cuckoo->insertItem(12);
    cuckoo->printTables();
    cout << "expected rehash." << endl << endl;
    // 5 % 4 = 1, floor(5 / 4) = 1 
    cout << "insert key: 5" << endl;
    cuckoo->insertItem(5);
    cuckoo->printTables();
    cout << "expected displacement without rehashing" << endl << endl;
    return 0;
}