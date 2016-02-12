#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include <list>
#define MAX 100
using namespace std;
class Room
{
private:
    int** room;

    pair<int , int> roomSize;
    pair<int , int> Tom;
    pair<int , int> Jerry;
    list < pair < int , int > > paintSpillsCoords;
    void copyRoom(int**);
    void myCopy(Room&);
    void createRoom();
    bool checkForPaintSpot(int ,int);


public:
    // BIG 4
    Room();
    ~Room();
    Room operator=(Room&);
    Room(Room&);
    // end of BIG 4
    void printRoom();

    void printPathsFromTomToJerry();
};
#endif
