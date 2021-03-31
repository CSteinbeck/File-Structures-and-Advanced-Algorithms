#include <fstream>
#include <sstream>
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
        return out;
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
   map<string, Album> albums;
     string name; // Artist's name
     int time;    // Total time of all songs on all albums by this artist
     int nsongs;  // Total number of songs on all albums by this artist
     bool operator < (Artist another) const { return name < another.name;}
};

string timeOutput(int &totalSeconds)
{
  int mins= totalSeconds/60;
  int seconds= totalSeconds%60;
  
  string r= to_string(mins)+ ":";
  if(seconds<10)
  {
    r+='0';
  }
  r += to_string(seconds);
  
  return r;
}

//Method to clean the string
string cleanString(string mess)
{
  for(int i=0; i<mess.length(); i++)
  {
    if(mess[i] == '_')
    {
      mess[i];
    }
  }
  return mess;
}


void formatFile(fstream &RawMusicFile)
{
  if(!RawMusicFile.is_open())
  {
    cout<<"File cannot be opened"<<endl;
  }
  Song s;
  Album al;
  Artist a;
  map<string, Artist> artistMap;
  map<string, Album> albumMap;
  map <string,Artist> :: iterator itr;
  map<string, Album> :: iterator itr2;
  map<int,Song> :: iterator itr3;
  string str;
  char ch;

  while(getline(RawMusicFile,str)) //Inputs the file in string by string and checking for an eof tag
  {
    //Breaks up all the items via stringstream (Broken by spaces)
    string title, time, artist, album, genre, track;
    int mins, secs; char colon;
    //cout<<str<<endl; //Test Print
    stringstream s1(str);
    s1>>title;
    title= cleanString(title);
    s1>>mins;
    s1>>colon;
    s1>>secs;
    int totalSeconds = (mins*60)+secs;
    s1>>artist;
    artist= cleanString(artist);
    s1>>album;
    album= cleanString(album);
    s1>>genre;
    s1>>track;
    
    if(artistMap.count(artist)>0) //If the artist already exist in the map
    {
      a.time= a.time + totalSeconds;
      a.nsongs++;

    }
    else{
        a.name= artist;
        a.time= totalSeconds;
        a.nsongs= 1;
        artistMap[artist]=a; //At this specific artist, added the artist a to the map(key) with the specifc name (value)
        //cout<<"Artist"<<endl;
    }

    if(artistMap.at(artist).albums.count(album)> 0)
    {
      artistMap.at(artist).albums.at(album).nsongs++; //Adds to the number of songs
      artistMap.at(artist).albums.at(album).time += totalSeconds; //Adds to the total time
    }
    else{
      al.artist= artist;
      al.time= totalSeconds;
      al.nsongs=1;
      al.genre =genre;
      artistMap.at(artist).albums[album] = al;
      //cout<<"Album"<<endl;

    }

    s.title= title;
    s.time = totalSeconds;
    s.track= stoi(track);
    artistMap.at(artist).albums.at(album).songs[stoi(track)]= s;
    //cout<<"Song"<<endl;
    
  }
  for(itr = artistMap.begin(); itr!= artistMap.end(); ++itr)
  {
    cout<<itr->first<<": "<<itr->second.nsongs<<timeOutput(itr->second.time)<<endl;
    
    for(itr2 = itr->second.albums.begin();itr2 !=itr->second.albums.end(); ++itr2)
    {
      cout<<"\t"<<itr2->first<<itr2->second.nsongs<<","<<timeOutput(itr2->second.time)<<endl;
      
      for(itr3 = itr2->second.songs.begin(); itr3 != itr2->second.songs.end(); ++itr3)
      {
        cout<<"\t\t"<<itr3->first<<"."<<itr3->second.title<<" "<<timeOutput(itr3->second.time)<<endl;
        
      }
    }

  }
}
int main(int argc, char *argv[])
{
  if(argc < 2) //Error Checking
  {
    cout<<"mp3: Missing filename 'mp3' "<<endl;
  } 
  string filename= argv[1];
  fstream RawMusicFile(filename.c_str(), ios :: in); //Pumps into a fstream to read in
  formatFile(RawMusicFile);

  return 0;
}