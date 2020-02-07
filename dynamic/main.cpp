#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

int M[1001][1001];

void checkmerge(string first, string second, string result, string &final){
    first = "0" + first;
    second = "0" + second;
    result = "0" + result;
    int i = first.length();
    int j = second.length();
    int k = result.length();

    memset(M, 0, sizeof(M));

    if(i+j-1!=k) final = "*** NOT A MERGE ***";
    else{
        for(int y=0;y<j;y++){
            if(second[y]==result[y]) M[y][0]=1;
            else M[y][0] = 0;
            if((M[y-1][0]==0)&&(y!=0)) M[y][0] = 0;
        }
        for(int x=0;x<i;x++){
            if(first[x]==result[x]) M[0][x]=1;
            else M[0][x] = 0;
            if((M[0][x-1]==0)&&(x!=0)) M[0][x] = 0;
        }
        for(int y=1;y<j;y++){
            for(int x=1;x<i;x++){
                if((M[y][x-1]==0)&&(M[y-1][x]==0)) M[y][x] = 0;
                else if(((first[x]==result[x+y])&&(M[y][x-1]==1))||((second[y]==result[x+y])&&(M[y-1][x]==1))) M[y][x] = 1;
                else M[y][x] = 0;
            }
        }

        if(M[j-1][i-1]==1){
            int x = i-1, y = j-1;
            while((x>0)||(y>0)){
                if((M[y-1][x]==1)&&(result[x+y]==second[y])) y--;
                else if((M[y][x-1]==1)&&(result[x+y]==first[x])){
                    result[x+y] = toupper(result[x+y]);
                    x--;
                }
            }
            final = result.substr(1,k);
        }
        else final = "*** NOT A MERGE ***";
    }
}

int main(){
    ifstream infile;
    ofstream outfile;
    string inName, outName, line, first, second, result;
    string final;
    int lineNUM = 0;

    cout << "Enter name of input file: ";
    cin >> inName;
    infile.open(inName);
    cout << "Enter name of output file: ";
    cin >> outName;
    outfile.open(outName);

    while(getline(infile, line)){
        lineNUM++;
        if(lineNUM%3 == 1)
            first = line;
        else if(lineNUM%3 == 2)
            second = line;
        else if(lineNUM%3 == 0){
            result = line;
            checkmerge(first,second,result,final);
            outfile << final << endl;
        }
    }
}