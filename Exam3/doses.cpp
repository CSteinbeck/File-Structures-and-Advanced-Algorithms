#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <memory>
#include <set>
#include<vector>

using namespace std;

void oneDose(fstream &file1, fstream &file2)
{
    //Created the needed iterators and sets for comparision//
    set<string>:: iterator itr;
    set<string>:: iterator itr2;
    set<string>:: iterator itr3;
    set<string>s1;
    set<string>s2;
    set<string>s3;
    string name1;
    string name2;
    char ch;
   while(file1 && file2)
   {
       while(!file1.eof())
       {
        file1>>name1;
        s1.insert(name1);
       }
       while(!file2.eof())
       {
           file2>>name2;
           s2.insert(name2);
       }
   }
   for (itr= s1.begin(); itr !=s1.end(); ++itr)
   {
        if(s2.find(*itr) == s2.end())
        {
            s3.insert(*itr);

        }
   }
    for (itr2= s2.begin(); itr2 !=s2.end(); ++itr2)
   {
        if(s1.find(*itr2) == s1.end())
        {
            s3.insert(*itr2);

        }
   }
    for (itr3= s3.begin(); itr3 !=s3.end(); ++itr3)
    {
        
        cout<< *itr3<<endl;
    }
}

int main(int argc, char *argv[])
{
    fstream file1("file1.txt", ios:: in);
    fstream file2("file2.txt", ios :: in);
    oneDose(file1, file2);   
    return 0;
}