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
    int difference;
    vector<int> compressionVector;
    string result= " "; int num; 
    stringstream s1(myInput);
    stringstream outputStream;
    while(s1>>num)
    {
         compressionVector.push_back(num);

            int freq = count(compressionVector.begin(),compressionVector.end(),num); //Identifies the frequency as the number of times that number appears
            if(freq < 4)
            { 
                outputStream<<num;
                outputStream<<" ";
            }
            else
            {
              outputStream<< "ff ";
              outputStream <<num << " ";
              outputStream<<freq<< " "; 
              do{
                s1>>num;
                freq--;
              }while(freq>1); 
            }

         }

        result= outputStream.str();
        return result;
    }
    


// string uncompress(string &cResult)
// {
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