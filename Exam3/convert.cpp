#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

int convertTime(string &time)
{
    int mins,secs; char colon;
    stringstream s1(time);
    s1>>mins;
    s1>>colon;
    s1>>secs;
    int totalSeconds = (mins*60)+secs;
    return totalSeconds;
}

int main(int argc, char *argv[])
{
    string time =argv[1];
    convertTime(time);
}