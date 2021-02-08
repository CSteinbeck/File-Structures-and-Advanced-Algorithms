#include <iostream>
#include <cstdlib>
#include <fstream>


using namespace std;

int MonthCheck(string month)
{
    int MonthNum;
    if(month == "January"){MonthNum =1;}
    if(month == "February"){MonthNum =2;}
    if(month == "March"){MonthNum =3;}
    if(month == "April"){MonthNum =4;}
    if(month == "May"){MonthNum =5;}
    if(month == "June"){MonthNum =6;}
    if(month == "July"){MonthNum =7;}
    if(month == "August"){MonthNum =8;}
    if(month == "September"){MonthNum =9;}
    if(month == "October"){MonthNum =10;}
    if(month == "November"){MonthNum =11;}
    if(month == "December"){MonthNum =12;}

    return MonthNum;
}

int main (int argc, char *arv[])
{
    string input, month;
    cout<< "Please enter a date you wish to convert:"<<endl;
    cin>>input;
    string finalOutput =""; //String that we want to append to for the final output
    for(int i =0; i <= input.size(); i++) //Loops through the string
    {
        if(input[i]== ','){i.ignore();}
        if(input[i]== ' ') //if it is a white space
        {
        
            string tmp =input.substr(0,i); //Make a substring for it
        }
    }
    
}