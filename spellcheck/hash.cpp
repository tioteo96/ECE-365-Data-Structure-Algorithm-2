#include <iostream>
#include "hash.h"

hashTable::hashTable(int size){
    capacity = getPrime(size);
    data.resize(capacity);
    filled = 0;

    for(int i=0;i<capacity;i++){
        data[i].isOccupied = false;
        data[i].isDeleted = false;
    }
}
//0=succes, 1=already exist, 2=rehash fail
int hashTable::insert(const std::string & key, void *pv){
    if(contains(key)) return 1;
    int pos = hash(key);
    while(data[pos].isOccupied) pos++;
    data[pos].key = key;
    data[pos].isOccupied = true;
    filled++;

    if(2*filled>capacity){
        if(!rehash()) return 2;
    }

    return 0;
}

bool hashTable::contains(const std::string &key){
    if(findPos(key)!=-1) return true;
    return false;
}

//---------------------------------------------------------------------

int hashTable::hash(const std::string &key){
    unsigned int hashVal = 0;
    for(char ch: key)
        hashVal = 37 * hashVal + ch;

    return hashVal % capacity;
}

int hashTable::findPos(const std::string &key){
    int pos = hash(key);
    while(data[pos].isOccupied){
        if(data[pos].key == key){
            if(!data[pos].isDeleted){
                return pos;
            }
            else return -1;
        }
        else pos++;
    }
    return -1;
}

bool hashTable::rehash(){
    int prev = capacity;
    std::vector<hashItem> temp = data;
    try{
        capacity = getPrime(prev*2);
        data.resize(capacity);
    }
    catch(std::bad_alloc &exc){
        return false;
    }

    for(int i=0;i<capacity;i++){
        data[i].isOccupied = false;
        data[i].isDeleted = false;
        //data[i].key = "";
    }
    filled = 0;
    for(int i=0;i<prev;i++){
        if(temp[i].isOccupied && !temp[i].isDeleted){
            insert(temp[i].key);
        }
    }

    return true;
}

unsigned int hashTable:: getPrime(int size){
    static unsigned int prime[] = {98317, 196613, 393241, 786433, 1572869, 3145739, 6291469,
                                   12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};

    int i = 0;
    while(prime[i] < size) i++;

    return prime[i];
}