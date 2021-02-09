#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

string MonthCheck(string month)
{
    string MonthNum;
    if(month == "January"){MonthNum = "1";}
    if(month == "February"){MonthNum = "2";}
    if(month == "March"){MonthNum = "3";}
    if(month == "April"){MonthNum = "4";}
    if(month == "May"){MonthNum = "5";}
    if(month == "June"){MonthNum = "6";}
    if(month == "July"){MonthNum = "7";}
    if(month == "August"){MonthNum = "8";}
    if(month == "September"){MonthNum = "9";}
    if(month == "October"){MonthNum = "10";}
    if(month == "November"){MonthNum ="11";}
    if(month == "December"){MonthNum ="12";}

    return MonthNum;
}

int main (int argc, char *arv[])
{
    string input, month;
    string finalOutput = "";
    cout<< "Please enter a date you wish to convert:"<<endl;
    getline(cin, input); //Gets the whole line
    stringstream s1(input); //Reads in the input file
    string word; //Variable to hold the new word in
    s1>>word;
    //Calls upon the method of month check
    month = MonthCheck(word);
    finalOutput += month;

    //Loop through the rest of the file 
    for(int i = month.length(); i<=input.length(); i++)
    {
        if(isdigit(input[i])) //Checks if it is a digit
        {
            finalOutput += input[i]; //Adds the output to final output
        }       
    }
    cout<<finalOutput<<endl;
}