#ifndef _GRAPH_H
#define _GRAPH_H

#include "hash.h"
#include <list>
#include <string>

class graph{
public:
    graph(int capacity);

    void insert(std::string &inName);

    void dijkstra(const std::string &startname);

    void result(std::string &outName, std::string &startname);

    bool goodstart(const std::string &startname);


    //private:
    struct vertex;
    class edge{
    public:
        vertex* dest {nullptr};
        int weight;
    };

    class vertex{
    public:
        std::list<edge> adj;
        std::string name{""};
        bool known{false};
        int dist;
        vertex* path{nullptr};
    };

    std::list<vertex> vertices;
    hashTable history;

    //void printpath(std::string &vertexname, std::string &fullpath);
};

# endif