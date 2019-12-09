#include <iostream>
#include <chrono>
#include <fstream>
#include <math.h>
#include "hashLL.hpp"
#include "hashProbe.hpp"
#include "hash_BST.hpp"
#include "hashFunction.hpp"
#include "hashCuckoo.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
    ifstream dataFile;
    string fileName = argv[1];
    ifstream inputFile (fileName);

    // Load factor for the tests being run
    float loadFactor = .2;

    cout << "Creating a table with LL collision implementation and hash function 0" << endl;
    HashTableLL* llHash0 = new HashTableLL(0);
    cout << "Creating a table with LL collision implemenation and hash function 1" << endl;
    HashTableLL* llHash1 = new HashTableLL(1);

    cout << "Creating a table with BST collision and hash function 0" << endl;
    HashTableBST* bstHash0 = new HashTableBST(0);
    cout << "Creating a table with BST collision and hash function 1" << endl;
    HashTableBST* bstHash1 = new HashTableBST(1);

    cout << "Creating a table with linear probing and hash function 0" << endl;
    HashTableProbe* probeHash0 = new HashTableProbe(0);
    cout << "Creating a table with linear probing and hash function 1" << endl;
    HashTableProbe* probeHash1 = new HashTableProbe(1);    

    cout << "Creating a table with cuckoo hasing" << endl;
    HashTableCuckoo* cuckooHash = new HashTableCuckoo();

    cout << "Getting a load factor of " << loadFactor << endl;
    int maxData1 = floor(loadFactor * TABLE_SIZE);
    int count  = 0;
    string line;
    int* firstDataSet = new int[100];

    // Read in enough data to get theg given load factor on all tables, then read the next 100 integers for testing
    while (getline(inputFile, line, ',') && count < maxData1+100) {
        int data = stoi(line);
        bool insertFail = false;
        // Insert the first integers to get a load factor of 0.1
        if (count < maxData1) {
            insertFail = !(llHash0->insertItem(data));
            llHash1->insertItem(data);
            bstHash0->insertItem(data);
            bstHash1->insertItem(data);
            probeHash0->insertItem(data);
            probeHash1->insertItem(data);
            cuckooHash->insertItem(data);
        } else {
            firstDataSet[count-maxData1] = data;
        }
        // Don't increment if a duplicate is tried to be added
        if (insertFail);
        else count++;
    }

    cout << "loading complete" << endl;
    
    /** =========================================== INSERTIONS =========================================== **/
    // Insert 100 into llHash0
    auto startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        llHash0->insertItem(firstDataSet[i]);
        auto time = std::chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<std::chrono::microseconds> (time-startTime).count();
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\nllHash0 insert average execution time: " << execTime << " microseconds" << endl;

    // Insert 100 into llHash1
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        llHash1->insertItem(firstDataSet[i]);
        auto time = std::chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<std::chrono::microseconds> (time-startTime).count();
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\nllHash1 insert average execution time: " << execTime << " microseconds" << endl;

    // Insert 100 into bstHash0
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        bstHash0->insertItem(firstDataSet[i]);
        auto time = std::chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<std::chrono::microseconds> (time-startTime).count();
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\nbstHash0 insert average execution time: " << execTime << " microseconds" << endl;

    // Insert 100 into bstHash1
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        bstHash1->insertItem(firstDataSet[i]);
        auto time = std::chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<std::chrono::microseconds> (time-startTime).count();
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\nbstHash1 insert average execution time: " << execTime << " microseconds" << endl;

    // Insert 100 into probe0
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        probeHash0->insertItem(firstDataSet[i]);
        auto time = std::chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<std::chrono::microseconds> (time-startTime).count();
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\nprobeHash0 insert average execution time: " << (execTime) << " microseconds" << endl;

    // Insert 100 into probe1
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        probeHash1->insertItem(firstDataSet[i]);
        auto time = std::chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<std::chrono::microseconds> (time-startTime).count();
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\nprobeHash1 insert average execution time: " << (execTime) << " microseconds" << endl;

    // // Insert 100 into cuckooo
    cout << "\nTo get to 'load factor' of " << loadFactor << ", " << cuckooHash->getNumRehashes() << " rehashes were needed" << endl;
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        cuckooHash->insertItem(firstDataSet[i]);
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "cuckooHash insert average execution time: " << (execTime) << " microseconds" << endl;
    cout << "cuckooHash required " << cuckooHash->getNumRehashes() << " rehashes" << endl;

    /** =========================================== LOOKUPS =========================================== **/
    // Search 100 in llHash0
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        llHash0->searchItem(firstDataSet[i]);
        auto time = std::chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<std::chrono::microseconds> (time-startTime).count();
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\nllHash0 lookup average execution time: " << execTime << " microseconds" << endl;

    // Search 100 in llHash1
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        llHash1->searchItem(firstDataSet[i]);
        auto time = std::chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<std::chrono::microseconds> (time-startTime).count();
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\nllHash1 lookup average execution time: " << execTime << " microseconds" << endl;

    // Search 100 in bstHash0
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        bstHash0->searchItem(firstDataSet[i]);
        auto time = std::chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<std::chrono::microseconds> (time-startTime).count();
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\nbstHash0 lookup average execution time: " << execTime << " microseconds" << endl;

    // Search 100 in bstHash1
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        bstHash1->searchItem(firstDataSet[i]);
        auto time = std::chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<std::chrono::microseconds> (time-startTime).count();
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\nbstHash1 lookup average execution time: " << execTime << " microseconds" << endl;

    // Search 100 in probe0
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        probeHash0->searchItem(firstDataSet[i]);
        auto time = std::chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<std::chrono::microseconds> (time-startTime).count();
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\nprobeHash0 lookup average execution time: " << (execTime) << " microseconds" << endl;

    // Search 100 in probe1
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        probeHash1->searchItem(firstDataSet[i]);
        auto time = std::chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<std::chrono::microseconds> (time-startTime).count();
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\nprobeHash1 lookup average execution time: " << (execTime) << " microseconds" << endl;

    // Search 100 in cuckooo
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        cuckooHash->searchItem(firstDataSet[i]);
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\ncuckooHash lookup average execution time: " << (execTime) << " microseconds" << endl;

    /** =========================================== DELETIONS =========================================== **/
    // Delete 100 from llHash0
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        llHash0->deleteItem(firstDataSet[i]);
        auto time = std::chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<std::chrono::microseconds> (time-startTime).count();
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\nllHash0 delete average execution time: " << execTime << " microseconds" << endl;

    // Delete 100 from llHash1
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        llHash1->deleteItem(firstDataSet[i]);
        auto time = std::chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<std::chrono::microseconds> (time-startTime).count();
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\nllHash1 delete average execution time: " << execTime << " microseconds" << endl;

    // Delete 100 from bstHash0
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        bstHash0->deleteItem(firstDataSet[i]);
        auto time = std::chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<std::chrono::microseconds> (time-startTime).count();
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\nbstHash0 delete average execution time: " << execTime << " microseconds" << endl;

    // Delete 100 from bstHash1
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        bstHash1->deleteItem(firstDataSet[i]);
        auto time = std::chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<std::chrono::microseconds> (time-startTime).count();
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\nbstHash1 delete average execution time: " << execTime << " microseconds" << endl;

    // Delete 100 from probe0
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        probeHash0->deleteItem(firstDataSet[i]);
        auto time = std::chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<std::chrono::microseconds> (time-startTime).count();
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\nprobeHash0 delete average execution time: " << (execTime) << " microseconds" << endl;

    // Delete 100 from probe1
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        probeHash1->deleteItem(firstDataSet[i]);
        auto time = std::chrono::high_resolution_clock::now();
        cout << chrono::duration_cast<std::chrono::microseconds> (time-startTime).count();
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\nprobeHash1 delete average execution time: " << (execTime) << " microseconds" << endl;

    // Delete 100 from cuckooo
    startTime = chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++ ) {
        cuckooHash->deleteItem(firstDataSet[i]);
    }
    endTime = std::chrono::high_resolution_clock::now();
    execTime = chrono::duration_cast<std::chrono::microseconds> (endTime-startTime).count();
    cout << "\ncuckooHash delete average execution time: " << (execTime) << " microseconds" << endl;

    return 0;
}