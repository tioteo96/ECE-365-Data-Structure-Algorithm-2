#include <iostream>
#include "heap.h"

heap::heap(int capacity):mapping(capacity*2){
    data.resize(capacity+1);
    filled = 0;
}

int heap::insert(const std::string &id, int key, void *pv){
    if(filled == data.size()-1) return 1;
    if(mapping.contains(id)) return 2;

    ++filled;

    data[filled].id = id;
    data[filled].key = key;
    data[filled].pData = pv;
    mapping.insert(data[filled].id, &data[filled]);

    percolateup(filled);

    return 0;
}

int heap::setKey(const std::string &id, int key){
    bool b;
    node* tmp = static_cast<node*>(mapping.getPointer(id, &b));
    if(!b) return 1;

    if(key<tmp->key){
        data[getPos(tmp)].key = key;
        percolateup(getPos(tmp));
    }
    else if(key>tmp->key){
        data[getPos(tmp)].key = key;
        percolatedown(getPos(tmp));
    }

    return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
    if(filled == 0) return 1;

    if(pId != nullptr) *pId = data[1].id;
    if(pKey != nullptr) *pKey = data[1].key;
    if(ppData != nullptr) *(static_cast<void **>(ppData)) = data[1].pData;
    mapping.remove(data[1].id);

    data[1] = std::move(data[filled--]);
    mapping.setPointer(data[1].id, &data[1]);
    percolatedown(1);

    return 0;
}

int heap::remove(const std::string &id, int *pKey, void *ppData){//decrease key and then deletemin
    bool b;
    node* tmp = static_cast<node*>(mapping.getPointer(id, &b));
    if(!b) return 1;

    if(pKey != nullptr) *pKey = data[getPos(tmp)].key;
    if(ppData != nullptr) *(static_cast<void **>(ppData)) = data[getPos(tmp)].pData;

    int tmpKey = data[1].key-1;
    setKey(id, tmpKey);
    deleteMin();

    return 0;
}

//---------------------------------------------------------------------

void heap::percolateup(int posCur){//
    data[0] = std::move(data[posCur]);
    for(;data[0].key<data[posCur/2].key;posCur/=2){
        data[posCur] = std::move(data[posCur/2]);
        mapping.setPointer(data[posCur].id, &data[posCur]);
    }
    data[posCur] = std::move(data[0]);
    mapping.setPointer(data[posCur].id, &data[posCur]);
}

void heap::percolatedown(int posCur){
    int child;
    data[0] = std::move(data[posCur]);

    for(;posCur*2<=filled;posCur=child){
        child = posCur*2;
        if(child!=filled && data[child+1].key<data[child].key)
            ++child;
        if(data[child].key<data[0].key){
            data[posCur] = std::move(data[child]);
            mapping.setPointer(data[posCur].id, &data[posCur]);
        }
        else
            break;
    }
    data[posCur] = std::move(data[0]);
    mapping.setPointer(data[posCur].id, &data[posCur]);
}

int heap::getPos(node *pn){
    return pn - &data[0];
}