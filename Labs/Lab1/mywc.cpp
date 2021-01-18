#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    string filename = argv[argc-1]; //starts count with executable
    fstream inOut (filename.c_str(), ios::in); //opened file with input+output mode
    int count = 0; 
    char ch;
    int lineCount=0;
    int wordCount=0;
    int byteCount=0;

    while(inOut.get(ch))
    {
        byteCount++;
        if(ch =='\n')
        {
            lineCount++;
            wordCount++;
        }

        if(ch == ' ' )
        {
            wordCount++;
        }
    }
    cout<<lineCount<<"\t"<<wordCount<<"\t"<<byteCount<<"\n";
}