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

bool flagCheck(int argc, char *argv[], bool &cfCheck, bool &tfCheck, bool &xfCheck, bool helpCheck)
{
    
    for (int i =0; i<argc; i++)
    {
        string str = argv[i];
        if(str == "-cf")
        {
            cfCheck =true;
             
        }
        else if(str == "-tf")
        {
            tfCheck= true;
            //tf();
        }
        else if(str == "-xf")
        {
            xfCheck= true;
            //xf();
        }
        else if(str == "--help")
        {
          printf("system cat help");  
        }        
        //Catches potentially illegal flags
        else if (str[0] == '-')
        {
            return false;
        }
    }
    return true;
}

void getFiles(vector<File> &f)
{
    for(auto p: recursive_directory_iterator(f))
        //cout << p.path() << '\n'; //Prints out the pathway for the file instead of the actual name
        f.push_back(getStats(p.path()));
}

//Gets all the relevant stat information for each file
File getStats(string files)
{
    stringstream s1;

    struct stat buf;
    lstat(files.c_str(), &buf); //populates the stat buff with the stats for the file
    //Prints the file name into  file object name
    //snprintf(name, 81, files.c_str()); //Prints into a string and includes n characters
    //Prints out the protection of the givem file
    s1<< ((buf.st_mode & S_IRWXU) >> 6) << ((buf.st_mode & S_IRWXG) >> 3) << (buf.st_mode & S_IRWXO);
   string pmode = s1.str();
   s1.clear();
   s1<<buf.st_size;
   string size =s1.str();
    char stamp[16]; 
    strftime(stamp, 16, "%Y%m%d%H%M.%S", localtime(&buf.st_ctime));
    bool isADirect = S_ISDIR(buf.st_mode); //Checks if the object is a directory
    File f(files.c_str(),pmode.c_str(), size.c_str(),stamp); //FILE OBJECT
    if(isADirect){f.flagAsDir();} //Flags as a directory
    return f;
}

//fileNum is number of files present and *files is the pointer to the array of files present 
void compress(int fileNum, string *files )
{
    vector<File>f;
    getFiles(f);

}
// void cf()
// {

// }

// void tf()
// {

// }

// void xf()
// {

// }






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
    if( flagCheck(argc, argv, cfCheck, tfCheck, xfCheck, helpCheck))
    {
        //comparision(argv[argc-2], argv[argc -1],iCheck, cCheck, num);

    }
    else{
        cerr<<"Invalid number of arguments"<<endl;
        cout<<"Please format your input accordingly: jtar [-cf] tarfile file1 dir1"<<endl;
        cout<<"Please format your input accordingly: jtar [-tf] tarfile"<<endl;
        cout<<"Please format your input accordingly: jtar [-xf] tarfile"<<endl;
        cout<<"Please format your input accordingly: jtar [--help]"<<endl;
    }
    return 0;
}