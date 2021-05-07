//Colton Steinbeck
//Test class for album.cpp 
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "album.h"

using namespace std;

int main(int argc, char* argv[])
{
    Album album;
    Album albumtest1;
    Album albumtest2;

    String one="00020";
    String two="Colton Steinbeck";
    String three="Test Name";
    
    Album AlbumCreated(one,two,three);//Manually creates an album to test album.cpp
    Album AlbumCreatedCopy(AlbumCreated);//Makes a copy of the album that we create above
    
    string fileName="album.baby";
    fstream inputFile;
    int i=1;

    inputFile.open(fileName.c_str(),ios::in); //Opens the file based on input
    cout<<endl;

    //Reads in and outputs albums that are in the file
    while(inputFile.eof()==false)
    {
       inputFile>>album; //Reads in the album object that we created
       cout <<"Album Info "<<i<<": "<<album<<endl; //Prints info
       cout<<"Get UPC: "<<album.getUPC()<<endl; //Prints out the UPC
       cout<<"Record Size: "<<album.recordSize()<<endl; //Prints out recordSize of the album object

       if(i==1)
       {
           albumtest1=album;//Makes a blank album and fills it with the original album contents
       }
       if(i==2)
       {
           albumtest2=album;//Makes another album and fills it with the original album contents
       }
       cout<<endl;
       i++;
    }

    //Printing out manual made Album and its copy
    cout<<"The Created Album: "<<AlbumCreated<<endl;
    cout<<"The Copy of the Created Album:" <<AlbumCreatedCopy<<endl;

     //Album UPC Comparisons
    bool UPC1=AlbumCreated<AlbumCreatedCopy;
    bool UPC2=albumtest1<albumtest2;
    cout<<endl;
    cout<<"Same UPC Boolean 1: "<<UPC1<<endl;
    cout<<"Same UPC Boolean 2: "<<UPC2<<endl;
    cout<<endl;

    return 0;
}
