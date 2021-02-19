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
    compressionVector.push_back(prev); //Pushes the value in the vector
    while(s1>>num) //While you're reading in the number
    {
        if(num ==prev) //If the previous numvber is a duplicate
        {
          compressionVector.push_back(num); //Adds the current number to the array
        }
        else
        {
          int freq = count(compressionVector.begin(),compressionVector.end(),prev); //Identifies the frequency as the number of times that number appears
          if(freq >= 4) //If the frequency bot 
          {
            //Inputs the compression data
            outputStream<< "ff ";
            outputStream<< prev << " ";
            outputStream<< freq<< " ";
            compressionVector.clear();
          }
          else{
            //If the frequency is less than 4
            for(int i =0; i<=freq; i++){
              outputStream<< prev<< " "; 
              
            }
            compressionVector.clear(); //Clears the vector to test it again
          }
        }
        prev = num; //Sets the num 
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
              outputStream<< prev<< " "; //Prints the frequency of the number that is less than 4
              
            }
            compressionVector.clear();
          }
        //Outputs all items to result
        result= outputStream.str();
        return result;
    }
    


string uncompress(string &cResult)
{
  string curr;
  int count;
  stringstream s2(cResult);
  stringstream outputStream2;
  
 
  while(s2>>curr)
  {

    if(curr == "ff")
    {
      s2>>curr; //curr moves the stringstream to the string we want to print out
      s2>>count;
      for(int i=0; i<count;i++)
      {
        outputStream2<<curr<<" ";
      }
    }
    else{
      outputStream2<<curr<<" ";
    }

  }
  string result = outputStream2.str();
  return result;
}


int main(int argc, char *argv[])
{
    string result; //Final result character
    string myInput = "93 93 93 93 92 91 91 94 94 94 94 94 95 95 95 73 73 73 73 73 73 73";
    string cResult = compress(myInput);
    cout<<cResult<<endl;
    string uResult =uncompress(cResult);
    cout<<uResult<<endl;
    return 0;
}