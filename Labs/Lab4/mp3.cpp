#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

class Song {
public:
  string title;
  int time;
  int track;      // Primary key
  bool operator < (Song another) const { return title < another.title;}
};

ostream & operator << (ostream& out, Song & l) {     
        cout << l.track << ".  " << l.title << " " << l.time/100 << ":";
        if ((l.time % 100) < 10) cout << "0";
        cout << l.time % 100;
}

class Album {
  public :
    map<int, Song> songs;
    string name;  // Album's name
    string artist;
    string genre;
    int time;     // Total time of all songs on album
    int nsongs;   // Total number of songs on album
};

class Artist {
   public :
     string name; // Artist's name
     int time;    // Total time of all songs on all albums by this artist
     int nsongs;  // Total number of songs on all albums by this artist
     bool operator < (Artist another) const { return name < another.name;}
};

void formatFile(fstream &RawMusicFile)
{
  if(){}//If there is a underscore in the stringstream
}


int main(int argc, char *argv[])
{
  if(argc < 2) //Error Checking
  {
    cout<<"mp3: Missing filename 'mp3' "<<endl;
  } 
  string filename= argv[2];
  fstream RawMusicFile(filename.c_str(), ios :: in); //Pumps into a fstream to read in
  formatFile(RawMusicFile);

  return 0;
}