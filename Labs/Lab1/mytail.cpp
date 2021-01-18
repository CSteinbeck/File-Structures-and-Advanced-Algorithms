#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    int lineCount;
    char ch;
    int n = (-1*(atoi(argv[1]))); //negates the value and reads i the value
    string filename = argv[2];

    ifstream ReadFile (filename.c_str(), ios :: in);

    //Starts the tail process at the eof
    ReadFile.seekg(-1,ios::end);

    bool first = false; //
    //Reads through the file from bottom to top
    while(lineCount < n)    
    {
        ReadFile.get(ch); //Read the character
        if(ch == '\n' && !first)
        {
            ch =' '; //Sets the first character is empty
        } //If the first character in the new line is a /n
        first =true;
         
        //If the character is a newline
        if(ch == '\n') 
        {
            lineCount++;
        }

        //If the line count is equal to n
        if(lineCount == n)
        {
            break;
        }
        ReadFile.seekg(-2 ,ios::cur); //One step forward, two steps back mentality  
        
        if(ReadFile.tellg()==0) //If the number is Out of Bounds
        {
            break;
        }
    }
    //Prints out the file
    while(ReadFile.get(ch))
    {
        cout<<ch;
    }    
}