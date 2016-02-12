#ifndef READERFORTNJ_H
#define READERFORTNJ_H
#include <iostream>
#include <string>
#include <list>
using namespace std;

class ReaderForTnJ
{
public:
///arguments
    pair<int , int> roomSize;
    pair<int , int> Tom;
    pair<int , int> Jerry;
    list<pair < int , int > > paintSpillCoords;
    int numberOfFurniture;
    int numberOfPaintSpills;
    int ** room;
/// non important functions
    void myCopy(ReaderForTnJ&);//
    void copyRoom(int **);//
    void createRoom();//
    void fillRoomWithZero();//
///functions
    ReaderForTnJ();
    ~ReaderForTnJ();//
    ReaderForTnJ(ReaderForTnJ&);//
    ReaderForTnJ& operator=(ReaderForTnJ&);//
};
#endif // READERFORTNJ_H
