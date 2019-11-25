#include <iostream>
#include <ctime>
#include <fstream>
#include <math.h>
#include "hashLL.hpp"
#include "hashProbe.hpp"
#include "hashFunction.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
    int startTime, endTime;
    double execTime;
    ifstream dataFile;
    string fileName = argv[1];
    ifstream inputFile (fileName);

    cout << "Creating a table with LL collision implementation and hash function 0" << endl;
    HashTableLL* llHash0 = new HashTableLL(0);
    cout << "Creating a table with LL collision implemenation and hash function 1" << endl;
    HashTableLL* llHash1 = new HashTableLL(1);
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
            probeHash0->insertItem(data);
            probeHash1->insertItem(data);
        } else {
            firstDataSet[count-maxData1] = data;
        }
        // cout << count << endl;
        if (insertFail);
        else count++;
    }

    startTime = clock();
    /*
    EVALUATION CODE GOES HERE
    */
    endTime = clock();
    execTime = (double)(endTime-startTime)/CLOCKS_PER_SEC;
    cout << "execution time: " << execTime << endl;

    cout << "\nPrinting LL Hash Table with Hash Function 0: " << endl;
    llHash0->printTable();
    cout << "\nPrinting LL Hash Table with Hash Function 1: " << endl;
    llHash1->printTable();
    cout << "\nPrinting Probing Hash Table with Hash Function 0: " << endl;
    probeHash0->printTable();
    cout << "\nPrinting Probing Hash Table with Hash Function 1: " << endl;
    probeHash1->printTable();
    return 0;
}