#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

bool flagCheck(int argc, char *argv[], int &num, bool &cCheck, bool &iCheck)
{
    
    for (int i =0; i<argc; i++)
    {
        string str = argv[i];
        if(str == "-c")
        {
            cCheck =true;   
        }
        else if(str == "-i")
        {
            iCheck= true;
            num =atoi(argv[i+1]); 
        }
        //Catches potentially illegal flags
        else if (str[0] == '-')
        {
            return false;
        }
    }
    return true;
}


void comparision(char *filename1, char *filename2, bool &iCheck,bool &cCheck, int &num)
{
    char ch1;
    char ch2;
    int lineCount=1;
    int byteCount=num;
    fstream file1(filename1, ios :: in);
    fstream file2(filename2, ios :: in);

    if(!file1){cout<<filename1<<" does not exist"<<endl; return;}
    if(!file2){cout<<filename2<<" does not exist"<<endl; return;}

    if(iCheck)
    {
        file1.seekg(num);
        file2.seekg(num);
    }
    while(file1 && file2) //While files are not EOF
    {
        file1.get(ch1);
        file2.get(ch2);

        byteCount++; //Keeps the byte accurate to the actual cmp command
        if(ch1 != ch2)
        {
            //Prints the generic differ output for file1 and file2
            cout<<filename1<<" "<<filename2<< " differ:  byte "<<byteCount<<", line "<<lineCount;
            if(cCheck)
            {
                printf(" is %o %c %o %c", ch1, ch1, ch2, ch2); //Prints the octal value and the characters needed for the -c flag
            }
            cout<<endl; //Prints the entire line
            return; //Prints the first time it differs
        }
        else if (ch1 == '\n')
        {
           lineCount++;
        }
        

    }
    if(!file1 && file2){
        cout<<"cmp: EOF on " <<filename1<<endl;
    }
    if(file1 && !file2){
        cout<<"cmp: EOF on " <<filename2<<endl;
    }

}


//Main function to run the other functions
int main (int argc, char *argv[])
{
    int num =0;
    bool cCheck = false;
    bool iCheck= false; 
    if(argc > 6 || argc < 3)
    {
        cerr<<"Invalid amount of arguments"<<endl;
    }
    if( flagCheck(argc, argv, num, cCheck, iCheck))
    {
        comparision(argv[argc-2], argv[argc -1],iCheck, cCheck, num);
    }
    else{
        cerr<<"Invalid number of arguments"<<endl;
        cout<<"Please format your input accordingly: cmp [-c] [-i number] file1 file2"<<endl;
    }
    return 0;  
}


