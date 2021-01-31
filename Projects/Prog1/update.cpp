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

void AddRec(map <long long, long> &m,  TransactionRec &T, int count, fstream &in, fstream &errors)
{
   BookRec r;
   if(m.count(T.B.isbn)>0)
   {
       errors<<"Error in transaction number: "<<count<<". Cannot add- duplicate "<< T.B.isbn <<endl;
   }
   else
   {
       in.seekp(0,ios :: end); //Puts file to the end
       in.write((char *) &T.B, sizeof(T.B)); //Puts the new isbn in the copy.out file
       m[T.B.isbn] =in.tellg(); //Puts it in the map
       
   }
}

void DeleteRec(map <long long, long> &m, TransactionRec &T, int count, fstream &in, fstream &errors)
{
    if(m.count(T.B.isbn) == 0)
    {
        errors<<"Error in transaction number"<<count<<" cannot delete - no such key"<< T.B.isbn <<endl;
    }
    else{
        m.erase(T.B.isbn); //Deletes the isbn from the map
    }

}

void ChangeRecOnHand(map <long long, long> &m, TransactionRec &T, int count, fstream &in, fstream &errors)
{
    
    int onhands =T.B.onhand;
    //Checks if it exists
    if(m.count(T.B.isbn) == 0)
    {
        errors<<"Error in transaction number"<<count<<" cannot count - no such key"<< T.B.isbn <<endl;
    }
    //Checking if it is a negative number
    else
    {
        //Points the pointer to the start and adds it
        BookRec r;
        in.seekg(m[T.B.isbn]-sizeof(T.B), ios ::beg);
        in.read((char *) &r, sizeof(T.B)); //Putting the new isbn to a generic bookrecord struct

        int difference = onhands + r.onhand; 

        if(difference < 0)
        {
            errors<<"Error in transaction number: "<<count<<"count == "<<difference<<" for key"<< T.B.isbn <<endl;
            r.onhand = 0;
        }
        else{
            //Must update the structs value
            r.onhand= onhands;
        }
        in.seekg(m[T.B.isbn] ios ::beg);
        in.write((char *) &r, sizeof(T.B)); //Writes the updated r value to the new map
    }
    
}

void ChangeRecPrice(map <long long, long> &m, TransactionRec &T, int count, fstream &in, fstream &error)
{
    int recPrice =T.B.price;
    BookRec r;
    if(m.count(T.B.isbn) == 0)
    {
        error<<"Error in transaction number"<<count<<" cannot change price --no such key"<< m[T.B.isbn] <<endl;
    }
    else{
        //Goes to the isbn needed
        in.seekg(m[T.B.isbn]-sizeof(T.B), ios ::beg);
        in.read((char *) &r, sizeof(T.B)); //Putting the new isbn to a generic bookrecord struct, pointer is now at the end of the specific bookrec
        r.price= recPrice; //Changes the price
        in.seekg(m[T.B.isbn]-sizeof(T.B), ios ::beg); //Points back at the beginning of the file
        in.write((char *) &r, sizeof(T.B)); //Writes new price to the file
        
    }
    
}

void printMap(map <long long, long> &m)

{
    map<long long, long>::iterator itr; 
    for(itr =m.begin(); itr != m.end(); ++itr)
    {
        cout << '\t' << itr->first << '\t' << itr->second << '\n'; 
    }
}

void PrintRecord(BookRec b)
{
    cout<<setw(10)<<setfill('0')<<b.isbn
        <<setw(25)<<setfill(' ')<<b.name
        <<setw(25)<<b.author
        <<setw(3)<<b.onhand
        <<setw(6)<<b.price
        <<setw(10)<<b.type<<endl;
}

/////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{

 TransactionRec T;
   if(argc ==4)
   {
    system("cp library.out copy.out");
   }

    //
    fstream in("copy.out", ios::in | ios :: out| ios::binary);
    fstream out (argv[3], ios :: in | ios ::out |ios :: binary);
    fstream errors("ERROR", ios :: out );
    //Creates a Map to store the ISBN's and their byte offsets
    map<long long,long > BookMap;

    //While the file is being read into // 
    while (in.read((char *) &T.B, sizeof(BookRec) ) )
	{
        //Mapped the key value (isbn) to the byte offset (in.tellg())
        BookMap[T.B.isbn] =in.tellg(); //when calling it, remeber to move it back 25 to account for it    
	}
    in.clear();


    //Passing in the transaction record to be read and processed
    fstream transCheck(argv[2], ios :: in| ios :: binary);
    int count =0;
    ///While reading in the transaction file
    while(transCheck.read((char *) &T, sizeof(TransactionRec) ))
    {       
            count++;
            //cout<<T.B.isbn<<endl;
            //Conditionals for each of the Transaction Records
            if(T.ToDo == 0)
            {
                //cout<< "Adding ISBN"<<endl;
                AddRec(BookMap, T, count, in, errors);
                
            }
            else if(T.ToDo == 1)
             {
                 //cout<< "Deleting ISBN"<<endl;
                 DeleteRec(BookMap, T, count, in, errors);
             }
            else if(T.ToDo == 2)
             {
                 //cout<< "Changing On Hand Amount"<<endl;
                 ChangeRecOnHand(BookMap, T, count, in, errors);
             }
            else if(T.ToDo == 3)
             {
                 //cout<<"Changing Price"<<endl;
                 ChangeRecPrice(BookMap,T, count, in, errors);
             }
        
       
    }
    transCheck.close(); //Closes the file 
    //loops through the updated map to 
    map<long long, long>::iterator itr;
    BookRec r; //Generic BookRecord to store
    for(itr =BookMap.begin(); itr != BookMap.end(); ++itr)
    { 
        
        //Read and write byte offset into the new file
       in.seekg(itr->second - sizeof(BookRec), ios ::beg);
       in.read((char *) &r, sizeof(T.B)); //puts into the bookrecord object
       PrintRecord(r);
       out.write((char *) &r, sizeof(T.B)); //Writes outs the Book record to be red 
    }
    out.close();
    system("rm copy.out");
    return 0;
}