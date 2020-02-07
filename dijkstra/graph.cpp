#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <climits>
#include "graph.h"
#include "heap.h"

using namespace std;

graph::graph(int capacity):history(capacity*2){

}

void graph::insert(string &inName){
    ifstream infile;
    string line, from, to, weight;
    infile.open(inName);

    while(getline(infile, line)){
        istringstream iss(line);
        iss >> from >> to >> weight;
        vertex vertex_from, vertex_to;

        if(!history.contains(from)){
            vertex_from.name = from;
            vertex_from.dist = INT_MAX;
            vertex_from.known = false;
            vertex_from.path = nullptr;
            vertex_from.adj = {};

            vertices.push_back(vertex_from);
            history.insert(from, &vertices.back());
        }
        if(!history.contains(to)){
            vertex_to.name = to;
            vertex_to.dist = INT_MAX;
            vertex_to.known = false;
            vertex_to.path = nullptr;
            vertex_to.adj = {};

            vertices.push_back(vertex_to);
            history.insert(to, &vertices.back());
        }

        vertex* to_p = static_cast<vertex*>(history.getPointer(to));
        vertex* from_p = static_cast<vertex*>(history.getPointer(from));

        edge edge_cur;
        edge_cur.dest = to_p;
        edge_cur.weight = stoi(weight);
        from_p->adj.push_back(edge_cur);
    }
    infile.close();
}

void graph::dijkstra(const string &startname){
    vertex* start = static_cast<vertex*>(history.getPointer(startname));
    heap HEAP(vertices.size());
    start->dist = 0;
    start->path = start;

    list<vertex>::iterator it_v;
    for(it_v=vertices.begin();it_v!=vertices.end();it_v++){
        HEAP.insert(it_v->name,it_v->dist,&(*it_v));
    }

    vertex* vertex_cur;

    while(HEAP.deleteMin(nullptr, nullptr, &vertex_cur)==0){

        list<edge>::iterator it_e;
        for(it_e=vertex_cur->adj.begin();it_e!=vertex_cur->adj.end();it_e++){
            if((it_e->dest->known==false)&&(vertex_cur->dist+it_e->weight < it_e->dest->dist)){
                it_e->dest->dist = vertex_cur->dist+it_e->weight;
                HEAP.setKey(it_e->dest->name, it_e->dest->dist);
                it_e->dest->path = vertex_cur;
            }
        }
        vertex_cur->known = true;
    }
}

void graph::result(string &outName, string &startname){
    ofstream outfile;
    outfile.open(outName);

    list<vertex>:: iterator it;
    for(it=vertices.begin();it!=vertices.end();it++){

        string to, path, pathlength;
        vertex v = *it;

        to = v.name;
        outfile << to << ": ";

        pathlength = to_string(it->dist);
        path = it->name;

        while(v.name!=startname){
            if(v.dist==INT_MAX){
                path = "NO PATH";
                break;
            }
            else{
                v = *v.path;
                path = v.name + ", " + path;
            }
        }

        if(path=="NO PATH")
            outfile << path << endl;
        else
            outfile << pathlength << " [" << path << "]" << endl;

    }
    outfile.close();
}

bool graph::goodstart(const string &startname){
    return history.contains(startname);
}