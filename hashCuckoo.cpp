#include <iostream>
#include <iomanip>

#include "hashCuckoo.hpp"
#include "hashFunction.hpp"
int primes[530] = { 10009, 10037, 10039, 10061, 10067, 10069, 10079, 10091, 10093, 10099 
, 10103, 10111, 10133, 10139, 10141, 10151, 10159, 10163, 10169, 10177 
, 10181, 10193, 10211, 10223, 10243, 10247, 10253, 10259, 10267, 10271 
, 10273, 10289, 10301, 10303, 10313, 10321, 10331, 10333, 10337, 10343 
, 10357, 10369, 10391, 10399, 10427, 10429, 10433, 10453, 10457, 10459 
, 10463, 10477, 10487, 10499, 10501, 10513, 10529, 10531, 10559, 10567 
, 10589, 10597, 10601, 10607, 10613, 10627, 10631, 10639, 10651, 10657 
, 10663, 10667, 10687, 10691, 10709, 10711, 10723, 10729, 10733, 10739 
, 10753, 10771, 10781, 10789, 10799, 10831, 10837, 10847, 10853, 10859 
, 10861, 10867, 10883, 10889, 10891, 10903, 10909, 10937, 10939, 10949 
, 10957, 10973, 10979, 10987, 10993, 11003, 11027, 11047, 11057, 11059 
, 11069, 11071, 11083, 11087, 11093, 11113, 11117, 11119, 11131, 11149 
, 11159, 11161, 11171, 11173, 11177, 11197, 11213, 11239, 11243, 11251 
, 11257, 11261, 11273, 11279, 11287, 11299, 11311, 11317, 11321, 11329 
, 11351, 11353, 11369, 11383, 11393, 11399, 11411, 11423, 11437, 11443 
, 11447, 11467, 11471, 11483, 11489, 11491, 11497, 11503, 11519, 11527 
, 11549, 11551, 11579, 11587, 11593, 11597, 11617, 11621, 11633, 11657 
, 11677, 11681, 11689, 11699, 11701, 11717, 11719, 11731, 11743, 11777 
, 11779, 11783, 11789, 11801, 11807, 11813, 11821, 11827, 11831, 11833 
, 11839, 11863, 11867, 11887, 11897, 11903, 11909, 11923, 11927, 11933 
, 11939, 11941, 11953, 11959, 11969, 11971, 11981, 11987, 12007, 12011 
, 12037, 12041, 12043, 12049, 12071, 12073, 12097, 12101, 12107, 12109 
, 12113, 12119, 12143, 12149, 12157, 12161, 12163, 12197, 12203, 12211 
, 12227, 12239, 12241, 12251, 12253, 12263, 12269, 12277, 12281, 12289 
, 12301, 12323, 12329, 12343, 12347, 12373, 12377, 12379, 12391, 12401 
, 12409, 12413, 12421, 12433, 12437, 12451, 12457, 12473, 12479, 12487 
, 12491, 12497, 12503, 12511, 12517, 12527, 12539, 12541, 12547, 12553 
, 12569, 12577, 12583, 12589, 12601, 12611, 12613, 12619, 12637, 12641 
, 12647, 12653, 12659, 12671, 12689, 12697, 12703, 12713, 12721, 12739 
, 12743, 12757, 12763, 12781, 12791, 12799, 12809, 12821, 12823, 12829 
, 12841, 12853, 12889, 12893, 12899, 12907, 12911, 12917, 12919, 12923 
, 12941, 12953, 12959, 12967, 12973, 12979, 12983, 13001, 13003, 13007 
, 13009, 13033, 13037, 13043, 13049, 13063, 13093, 13099, 13103, 13109 
, 13121, 13127, 13147, 13151, 13159, 13163, 13171, 13177, 13183, 13187 
, 13217, 13219, 13229, 13241, 13249, 13259, 13267, 13291, 13297, 13309 
, 13313, 13327, 13331, 13337, 13339, 13367, 13381, 13397, 13399, 13411 
, 13417, 13421, 13441, 13451, 13457, 13463, 13469, 13477, 13487, 13499 
, 13513, 13523, 13537, 13553, 13567, 13577, 13591, 13597, 13613, 13619 
, 13627, 13633, 13649, 13669, 13679, 13681, 13687, 13691, 13693, 13697 
, 13709, 13711, 13721, 13723, 13729, 13751, 13757, 13759, 13763, 13781 
, 13789, 13799, 13807, 13829, 13831, 13841, 13859, 13873, 13877, 13879 
, 13883, 13901, 13903, 13907, 13913, 13921, 13931, 13933, 13963, 13967 
, 13997, 13999, 14009, 14011, 14029, 14033, 14051, 14057, 14071, 14081 
, 14083, 14087, 14107, 14143, 14149, 14153, 14159, 14173, 14177, 14197 
, 14207, 14221, 14243, 14249, 14251, 14281, 14293, 14303, 14321, 14323 
, 14327, 14341, 14347, 14369, 14387, 14389, 14401, 14407, 14411, 14419 
, 14423, 14431, 14437, 14447, 14449, 14461, 14479, 14489, 14503, 14519 
, 14533, 14537, 14543, 14549, 14551, 14557, 14561, 14563, 14591, 14593 
, 14621, 14627, 14629, 14633, 14639, 14653, 14657, 14669, 14683, 14699 
, 14713, 14717, 14723, 14731, 14737, 14741, 14747, 14753, 14759, 14767 
, 14771, 14779, 14783, 14797, 14813, 14821, 14827, 14831, 14843, 14851 
, 14867, 14869, 14879, 14887, 14891, 14897, 14923, 14929, 14939, 14947 
, 14951, 14957, 14969, 14983, 15013, 15017, 15031, 15053, 15061, 15073 };

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
    int newTableSize = primes[numRehashes];

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
            numRehashes++; 
            newTableSize = primes[numRehashes];
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