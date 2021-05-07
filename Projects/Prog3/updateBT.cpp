#include <iostream>
#include <cstdlib>
#include <fstream>
#include "btree.h"
#include "album.h"
using namespace std;

int main(int argc, char *argv[])
{
BTree t;
Album alpha;
string UPC;
t.writeHeader(argv[1]);
fstream transFile(argv[2], ios::in);
char symbol;
while(transFile>>symbol)
{
    transFile.ignore();
    if(symbol == 'S')
    {
        getline(transFile, UPC);
        if(t.search(UPC) ==true)
        {
            cout<<"It is true"<<endl;
            alpha = t.retrieve(UPC);
            cout<<alpha<<endl;
        }
        else{
            cout<<UPC<<" is not found"<<endl;
        }
    }
    if(symbol == 'I')
    {
        transFile>>alpha;
        t.insert(alpha);
        cout<<"Now Inserting"<<endl;
        cout<<alpha<<endl;

    }
    t.totalio();
    }
            
}