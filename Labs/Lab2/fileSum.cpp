#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

int fileSum(ifstream &input)
{
    int sum, tmp;
    while(!(input.eof()))
    {
        while(input>>tmp)
        {
            sum+=tmp;
        }
        input.clear();
        //If the input has a comma in it or the EOF with peek is -1
        if(input.peek() == ',' || input.peek() == -1)
        {
            input.ignore(1); //ignores 1 byte
        }
        else
        {
            sum = -1;
        }
        

    }
return sum;
}
int main(int argc, char *argv[])
{
    int result;
    string filename =argv[1];
    ifstream input(filename.c_str());
    result = fileSum(input);
    cout<< result<<endl;
}
