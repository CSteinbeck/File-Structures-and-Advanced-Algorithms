#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

string compress(string &myInput)
{   
    
    vector<int> compressionVector;
    string result= " "; int num; int prev = num;
    stringstream s1(myInput);
    stringstream outputStream;
    s1>>prev;
    compressionVector.push_back(prev);
    while(s1>>num)
    {
        if(num ==prev)
        {
          compressionVector.push_back(num);
        }
        else
        {
          int freq = count(compressionVector.begin(),compressionVector.end(),prev); //Identifies the frequency as the number of times that number appears
          if(freq >= 4)
          {
            outputStream<< "ff ";
            outputStream<< prev << " ";
            outputStream<< freq<< " ";
            compressionVector.clear();
          }
          else{
            for(int i =0; i<=freq; i++){
              outputStream<< prev<< " ";
              
            }
            compressionVector.clear();
          }
        }
        prev = num;   
    }
    int freq = count(compressionVector.begin(),compressionVector.end(),prev); //Identifies the frequency as the number of times that number appears
          if(freq >= 4)
          {
            outputStream<< "ff ";
            outputStream<< prev << " ";
            outputStream<< freq<< " ";
            compressionVector.clear();
          }
          else{
            for(int i =0; i<=freq; i++)
            {
              outputStream<< prev<< " ";
              
            }
            compressionVector.clear();
          }
        //Outputs all items to result
        result= outputStream.str();
        return result;
    }
    


// string uncompress(string &cResult)
// {
//   string curr; string prev;
//   stringstream s2(cResult);
//   s2>>prev;
//   while(s2>>curr)
//   {
//     if(curr =="ff")
//     {

//     }
//   }

//     string result;
//     return result;
// }


int main(int argc, char *argv[])
{
    string result; //Final result character
    string myInput = "93 93 93 93 92 91 91 94 94 94 94 94 95 95 95 73 73 73 73 73 73 73";
    string cResult = compress(myInput);
    cout<<cResult<<endl;
    // string uResult =uncompress(cResult);
    // cout<<uResult<<endl;
    return 0;
}