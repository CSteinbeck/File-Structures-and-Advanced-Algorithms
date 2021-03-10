//Colton Steinbeck
//jtar source file
#include <filesystem>
#include <sys/stat.h>
#include "file.h"
#include <cstring>
#include <vector>
#include <iostream>
#include <sys/types.h>
#include <cstdlib>
#include <utime.h>
#include <memory>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;
using recursive_directory_iterator = filesystem::recursive_directory_iterator;

//Gets all the relevant stat information for each file
File createFile(string files)
{
   stringstream s1;
   struct stat buf;


   lstat(files.c_str(), &buf); //populates the stat buff with the stats for the file
   s1<< ((buf.st_mode & S_IRWXU) >> 6) << ((buf.st_mode & S_IRWXG) >> 3) << (buf.st_mode & S_IRWXO);
   string pmode = s1.str();
   s1.clear();
   string size = to_string(buf.st_size);
    char stamp[16]; 
    strftime(stamp, 16, "%Y%m%d%H%M.%S", localtime(&buf.st_ctime));
    bool isADirect = S_ISDIR(buf.st_mode); //Checks if the object is a directory
    File f(files.c_str(),pmode.c_str(), size.c_str(),stamp); //FILE OBJECT
    if(isADirect){f.flagAsDir();} //Flags as a directory
    return f;
}


void getFiles(vector<File> &f, int& count)
{
    //File file;
    for(auto p: recursive_directory_iterator(f[0].getName())) //Loops through the file vector and pulls the correspoding directory and directory size to review 
    {    //cout << p.path() << '\n'; //Prints out the pathway for the file instead of the actual name
        f.push_back(createFile(p.path()));
        count++;
    }
}

//Compression of files 
int cf(int fileNum, string &fileName, fstream &binaryOut)
{
    
    vector<File>fVector;
    File f1= createFile(fileName); //Creates the file based on the file name
    
    int count = 0; //Keeps count of the number of items in the file
    if(f1.isADir())
    {
        fVector.push_back(f1); //Pushes to the Vector

        count++; //Increments the count of the # of files
        getFiles(fVector, count);
        
    }
    cout<<count<<endl;
    for(int i=0; i<count; i++)
    {
        //Writes out one file object in binary
        cout<<"prewrite"<<endl;
        binaryOut.write((char *) &fVector[i], sizeof(fVector[i])); //Writes the file contents into the binary file
        cout<<"Mid-write"<<endl;
        cout<<fVector[i].getName()<<endl; //Gets the name of the file
        cout<<"Post-write"<<endl;
        if(!fVector[i].isADir())
        {
            fstream openFile(fVector[i].getName().c_str(),ios ::in ); //Opens the vector 
            cout<<"T3"<<endl;
            cout<<fVector[i].getSize()<<endl;
            int newSize =atoi(fVector[i].getSize().c_str()); //Gets the size of the individual file for the project
            cout<<newSize<<endl;
            char contents[newSize]; //Creates an array based on the size of vector and stores the file vector into contents
            cout<<"T1"<<endl;
            openFile.read(contents, newSize); //Reads the vector contensts into a char array
            cout<<"T2"<<endl;
            binaryOut.write(contents, newSize); //Writes out the binary output
        }  
    }
    return fVector.size(); //Returns the # of files compressed
    
}

bool flagCheck(int argc, char *argv[], bool &cfCheck, bool &tfCheck, bool &xfCheck, bool &helpCheck)
{
    fstream binaryOut("tarfile", ios::out | ios::binary);

        string str = argv[1];
        if(str == "-cf")
        {
            cfCheck =true;
            int num =0;
            binaryOut.write((char* )&num, sizeof(num));
            for(int j=3; j<argc; j++)
            {
                string fileName =argv[j];
                int fileNum = j-3; //Keeps track of what file you're pulling in
                cout<<"FUCK"<<endl;
                num += cf(fileNum,fileName, binaryOut); //Compresses the file and collects the number of files that are compressed (One at the time)

            }
            binaryOut.seekg(0); //Points to the beginning of the file and preps to put the total number of files
            binaryOut.write((char *) &num, sizeof(num)); //writes out the size of the file to the binary output file
        }
        // else if(str == "-tf")
        // {
        //     tfCheck= true;
        // }
        // else if(str == "-xf")
        // {
        //     xfCheck= true;
        // }
        else if(str == "--help")
        {
          printf("system cat help");  
        }        
        //Catches potentially illegal flags
        else if (str[0] == '-')
        {
            return false;
        }
    return true;
}






int main(int argc, char *argv[])
{
    int num =0;
    File f;
    char tarfile;
    bool cfCheck = false;
    bool tfCheck = false;
    bool xfCheck= false;
    bool helpCheck = false; 
    if(argc > 6 || argc < 3)
    {
        cerr<<"Invalid amount of arguments"<<endl;
    }
    if(flagCheck(argc, argv, cfCheck, tfCheck, xfCheck, helpCheck)){}

    else{
        cerr<<"Invalid number of arguments"<<endl;
        cout<<"Please format your input accordingly: jtar [-cf] tarfile file1 dir1"<<endl;
        cout<<"Please format your input accordingly: jtar [-tf] tarfile"<<endl;
        cout<<"Please format your input accordingly: jtar [-xf] tarfile"<<endl;
        cout<<"Please format your input accordingly: jtar [--help]"<<endl;
    }
    return 0;
}