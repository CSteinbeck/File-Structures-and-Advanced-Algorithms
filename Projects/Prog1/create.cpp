//Colton Steinbeck
//Part II: Processing a Master File and Building a Binary File
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <climits>

using namespace std;

//Given Struct of Book Record
typedef char String[25];
struct BookRec
{
    unsigned int isbn;
    String name;
    String author;
    int onhand;
    float price;
    String type;
};


    void PrintRecord(BookRec b)
    {
        cout<<setw(10)<<setfill('0')<<b.isbn
	      <<setw(25)<<setfill(' ')<<b.name
	      <<setw(25)<<b.author
	      <<setw(3)<<b.onhand
	      <<setw(6)<<b.price
	      <<setw(10)<<b.type<<endl;
    }

int main(int argc, char* argv[])
{
    //Creates input file argument and reads it in
    BookRec BookInstance;
    string filename =argv[1]; //Filename is second parameter
    ifstream readInput (filename.c_str(), ios :: in | ios :: binary);
    string delta;
    long long tempIsbn;
    long savedIsbn;
    fstream output("library.out",ios :: out | ios :: binary);
    //Reading readInput into temp isbn
    while(readInput>>tempIsbn)
    {
        bool out = true; //The output can occur and go into the file, can stop records from being printed to the binary file
        readInput.ignore(1,'|'); //Ignore the first delimiter for the byte
        if(tempIsbn < 1)
        {
            cerr<<"Error: ISBN is invalid"<<endl;
            getline(readInput, delta); //Moves the needle from the error to the next isbn     
        }
        else
        {   
            //Defines items in the .dat file in context to the struct
            BookInstance.isbn = tempIsbn;
            readInput.getline(BookInstance.name,25, '|');
            readInput.getline(BookInstance.author,25, '|');
            readInput>>BookInstance.onhand;
            readInput.ignore(1,'|');
            readInput>>BookInstance.price;
            readInput.ignore(1,'|');
            readInput.getline(BookInstance.type, 25, '\n');
            

            if(tempIsbn < savedIsbn)
            {
                cerr<<"Isbn is out of order"<<endl;
            }
            if(BookInstance.price < 0)
            {
                cerr<<"Price is invalid"<<endl; 
                out = false; 
            }
            if(BookInstance.onhand <0)
            {
                cerr<<"There are no more copies on hand!"<<endl;
                out = false;
            }
            savedIsbn = BookInstance.isbn;
            
            //Type-casting into a char * and then being written into a binary file
            if(out)
            {
                output.write((char *) &BookInstance,sizeof(BookInstance));
            }
        }

    }
    readInput.close();
    output.close();


    //Printing out items in correspondance to library.out file
    ifstream output2("library.out", ios :: in | ios :: binary);
    //Prints values to the screen
    while(output2.read((char *) &BookInstance,sizeof(BookInstance)))
    {
        PrintRecord(BookInstance);
    }
}