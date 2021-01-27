//Colton Steinbeck
//Creation of the Database for Binary Books

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>
#include <iomanip>
#include <climits>

using namespace std;

//Needed emunerators and structs
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

enum TransactionType {Add, Delete, ChangeOnHand, ChangePrice};
struct TransactionRec
{
    TransactionType ToDo;
    BookRec B;
};


int main(int argc, char* argv[])
{
    //Copies 
    system("cp " + argv[1] + " copy.out");
    return 0;
}