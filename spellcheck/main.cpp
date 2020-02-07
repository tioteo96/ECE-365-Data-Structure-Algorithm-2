#include "hash.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <locale>
#include <cctype>

using namespace std;

void readDictionary(hashTable &HASH){
    ifstream dictionary;
    string dicName, line;
    clock_t time;

    cout << "Enter name of dictionary: ";
    cin >> dicName;
    dictionary.open(dicName);

    time = clock();
    while(getline(dictionary, line)){
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        HASH.insert(line);
    }
    time = clock() - time;
    double time_real = ((double)time)/CLOCKS_PER_SEC;
    dictionary.close();

    cout << "Total time (in seconds) to load dictionary: " << time_real << endl;
}

bool validchar(char c){
    if(!isdigit(c) && !isalpha(c) && c!='-' && c!='\'') return true;
    else return false;
}

bool containNUM(string &word){
    for(int i=0;i<word.size();i++){
        if(isdigit(word[i])) return true;
    }
    return false;
}

void spellcheck(hashTable &HASH){
    ifstream infile;
    ofstream outfile;
    string inName, outName, line;
    vector<string> word;
    clock_t time;
    int lineNUM = 0;

    cout << "Enter name of input file: ";
    cin >> inName;
    infile.open(inName);
    cout << "Enter name of output file: ";
    cin >> outName;
    outfile.open(outName);

    time = clock();
    while(getline(infile, line)){
        lineNUM++;
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        int i=0;
        for(int n=0;n<line.size();n++){
            if(validchar(line[n])||line[n]==' '){
                if(n!=i) word.push_back(line.substr(i, n-i));
                i = n+1;
            }
        }
        if(i!=line.size()){
            word.push_back(line.substr(i,line.size()-i));
        }
        for(int n=0;n<word.size();n++){
            if(containNUM(word[n])) continue;
            else if(word[n].size()>20){
                outfile << "Long word at line " << lineNUM << ", starts: " << word[n].substr(0,20) << endl;
            }
            else if(!HASH.contains(word[n])){
                outfile << "Unknown word at line " << lineNUM << ": " << word[n] << endl;
            }
        }
        word.clear();
    }
    time = clock() - time;
    double time_real = ((double)time)/CLOCKS_PER_SEC;

    cout << "Total time (in seconds) to check document: " << time_real << endl;
    infile.close();
    outfile.close();
}

int main(void){
    hashTable HASH(10);
    readDictionary(HASH);
    spellcheck(HASH);
}