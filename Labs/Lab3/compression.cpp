#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

string compress(stringstream &s1)
{
    string test1 = "Compression works";
    return test1;  
}

string uncompress(stringstream &s1)
{
    string test2 = "Uncompression works";
    return test2; 
}


int main(int argc, char *argv[])
{
    string result; //Final result character
    string userInput; //User input variable
    string number; //String to pass items into the string stream
    cout<<"Please enter the string: "<<endl;
    getline(cin, userInput); //Gets the user input
    stringstream s1(userInput); //Imports it into the stringstream
    while(s1>>number) //While the stream is being passed into the string number object
    {
        //cout<<number<<endl; --Test case for the stringstream
        if(number == "ff") //Checks if the stringstream is a compressed file
        {
            result = uncompress(s1); //Calls the Uncompression Function
        }
       result = compress(s1);
    }
    cout<<result<<endl;
    return 0;
}