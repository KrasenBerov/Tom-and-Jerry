#include "Room.h"
#include "ReaderForTnJ.h"
#include "recSearch.cpp"
///private stuff
void Room::copyRoom(int** _room)
{
    for(int i = 0 ; i < roomSize.first ; i ++)
        for(int j = 0 ; j < roomSize.second ; j ++)
            room[i][j] = _room[i][j];
}
void Room::myCopy(Room& r)
{
    roomSize = r.roomSize;
    copyRoom(r.room);
    Tom = r.Tom;
    Jerry = r.Jerry;
}
//creates room with known x y
void Room::createRoom()
{
    room = new int*[roomSize.second];
    for(int i = 0 ; i < roomSize.second ; i ++)
        room[i] = new int[roomSize.first];
}
bool Room::checkForPaintSpot(int _x , int _y)
{
    for(list<pair <int , int > >::iterator i = paintSpillsCoords.begin() ; i != paintSpillsCoords.end() ; i ++)
        if((*i) == pair<int,int>(_x , _y))
            return true;
    return false;
}

///public stuff
//BIG 4
Room::Room()
{
    ReaderForTnJ homeOwners;
    Tom = homeOwners.Tom;
    Jerry = homeOwners.Jerry;
    roomSize = homeOwners.roomSize;
    paintSpillsCoords = homeOwners.paintSpillCoords;
    createRoom();
    copyRoom(homeOwners.room);
}
Room::~Room()
{
    for(int i = 0 ; i < roomSize.second ; i++)
        delete[] room[i];
    delete[] room;
}
Room::Room(Room & r)
{
    myCopy(r);
}
Room Room::operator=(Room& r)
{
    if(this != &r)
        myCopy(r);
    return *this;
}
// end of BIG 4
void Room::printRoom()
{
    for(int i = 0 ; i < roomSize.first ; i ++)
    {
        cout << "|";
        for(int j = 0 ; j < roomSize.second ; j ++)
        {
            if(checkForPaintSpot(i , j))
                cout << "S|";
            else if(pair<int , int>(i,j) == Tom)
                cout << "T|";
            else if(pair<int ,int>(i,j) == Jerry)
                cout << "J|";
            else if(room[i][j] == -3)
                cout << "*|";
            else if(room[i][j] == 0)
                cout << " |";
        }
        cout << endl;
    }
}
void Room::printPathsFromTomToJerry()
{
    Matrix m(roomSize.first , roomSize.second , room , paintSpillsCoords);
    m.findPath(Tom.first, Tom.second , Jerry.first , Jerry.second);
    m.printAllPaths();
}
