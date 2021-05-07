#include <iostream>
#include <cstdlib>
#include <fstream>
#include "btree.h"
#include "album.h"



using namespace std;

int main(int argc, char *argv[])
{
    ifstream file(argv[1], ios:: in);
    BTree b;
    b.writeHeader(argv[2]);
    Album alpha;
    while(file >>alpha)
    {
        cout<<"Inserting Album: " <<alpha<<endl;
        b.insert(alpha);
        cout<<"Fininshed Inserting: "<<alpha<<endl;
        b.printTree();
        cout << endl << endl;
    }
    
    cout << "777777777777777777777777777777777777777777777777777" << endl;
    b.inorder();

}