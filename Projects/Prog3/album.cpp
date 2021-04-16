//Colton Steinbeck
//album.cpp class from .h file
#include "album.h"

Album:: Album(const Album& otherAlbum)
{
    strcpy (UPC, otherAlbum.UPC);
    strcpy (Artist, otherAlbum.Artist);
    strcpy (Title, otherAlbum.Title);
}

Album :: Album(String myUpc, String myArtist, String myTitle)
{
    strcpy(UPC, myUpc);
    strcpy(Artist, myArtist);
    strcpy(Title, myTitle);
}

Album ::Album()
{
    strcpy(UPC, "\0");
    strcpy(Artist, "\0");
    strcpy(Title, "\0");
}
Album & Album::operator = (const Album& otherAlbum)
{
       strcpy (UPC, otherAlbum.UPC);
       strcpy (Artist, otherAlbum.Artist);
       strcpy (Title, otherAlbum.Title);
       return *this;
}

bool operator <(const Album& a, const Album& b)
{
    return atoi(a.UPC) < atoi(b.UPC);
}

istream& operator >> (istream &stream, Album &C)
{
    stream.getline(C.UPC,50,'\n');
    stream.getline(C.Artist, 50, '\n');
    stream.getline(C.Title, 50, '\n');
    return stream;
}
ostream& operator<<(ostream &stream, Album& C)
{
    return stream<<C.UPC;
    return stream<<C.Artist;
    return stream<<C.Title;
    return stream;
}

string Album::getUPC()
{
    return UPC;
}

int Album::recordSize()
{
    return (strlen(UPC)+strlen(Artist)+strlen(Title));
}

