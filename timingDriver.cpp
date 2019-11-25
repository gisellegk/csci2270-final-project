#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <math.h>
#include "hashLL.hpp"
#include "hashProbe.hpp"
#include "hash_BST.hpp"
#include "hashFunction.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
    clock_t clockStart;
    int startTime, endTime;
    double execTime;
    ifstream dataFile;
    string fileName = argv[1];
    ifstream inputFile (fileName);

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

    cout << "Getting a load factor of 0.1" << endl;
    int maxData1 = floor(0.1 * TABLE_SIZE);
    int count  = 0;
    string line;
    int* firstDataSet = new int[100];

    // Read in enough data to get a load factor of 0.1 on all tables, then read the next 100 integers for testing
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
        } else {
            firstDataSet[count-maxData1] = data;
        }
        // cout << count << endl;
        if (insertFail);
        else count++;
    }

    // Insert 100 into llHash0
    double* ll0InsertTimes = new double[100];
    for (int i = 0; i < 100; i++ ) {
        auto startTime = chrono::high_resolution_clock::now();
        llHash0->insertItem(firstDataSet[i]);
        auto endTime = std::chrono::high_resolution_clock::now();
        chrono::duration<double> execTime = endTime-startTime;
        ll0InsertTimes[i] = execTime.count();
    }
    double ll0Sum = 0;
    for (int i = 0; i < 100; i++ ) {
        cout << " + " << ll0InsertTimes[i];
        ll0Sum += ll0InsertTimes[i];
    }
    cout << "\nllHash0 average execution time: " << (ll0Sum / 100) << endl;

    // Insert 100 into probe0
    double* probe0InsertTimes = new double[100];
    for (int i = 0; i < 100; i++ ) {
        auto startTime = chrono::system_clock::now();
        probeHash0->insertItem(firstDataSet[i]);
        auto endTime = std::chrono::system_clock::now();
        chrono::duration<double> execTime = endTime-startTime;
        probe0InsertTimes[i] = execTime.count();
    }
    double probe0Sum = 0;
    for (int i = 0; i < 100; i++ ) {
        cout << " + " << probe0InsertTimes[i];
        probe0Sum += probe0InsertTimes[i];
    }
    cout << "\nprobeHash0 average execution time: " << (probe0Sum / 100) << endl;

    // cout << "\nPrinting LL Hash Table with Hash Function 0: " << endl;
    // llHash0->printTable();
    // cout << "\nPrinting LL Hash Table with Hash Function 1: " << endl;
    // llHash1->printTable();
    // cout << "\nPrinting BST Hash Table with Hash Function 0:" << endl;
    // bstHash0->printTable();
    // cout << "\nPrinting BST Hash Table with Hash Function 1:" << endl;
    // bstHash1->printTable();
    // cout << "\nPrinting Probing Hash Table with Hash Function 0: " << endl;
    // probeHash0->printTable();
    // cout << "\nPrinting Probing Hash Table with Hash Function 1: " << endl;
    // probeHash1->printTable();
    return 0;
}