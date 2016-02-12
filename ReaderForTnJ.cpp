#include "ReaderForTnJ.h"

#include <fstream>
void ReaderForTnJ::myCopy(ReaderForTnJ & r)
{
    roomSize = r.roomSize;
    Tom = r.Tom;
    Jerry = r.Jerry;
    numberOfFurniture = r.numberOfFurniture;
    numberOfPaintSpills = r.numberOfPaintSpills;
    copyRoom(r.room);
    paintSpillCoords = r.paintSpillCoords;
}
void ReaderForTnJ::copyRoom(int** _room)
{
    for(int i = 0 ; i < roomSize.first ; i ++)
        for(int j = 0 ; j < roomSize.second ; j ++)
            room[i][j] = _room[i][j];
}
ReaderForTnJ::ReaderForTnJ()
{
    ifstream iFile;
    iFile.open("TheRoom.txt");
    if(iFile.is_open())
    {
        iFile >> roomSize.first;
        iFile >> roomSize.second;
        createRoom();
        fillRoomWithZero();
        iFile >> Jerry.first;
        iFile >> Jerry.second;
        iFile >> Tom.first;
        iFile >> Tom.second;
        iFile >> numberOfFurniture;
        iFile >> numberOfPaintSpills;
        for(int i = 0 ; i < numberOfFurniture ; i ++)
        {
            int first;
            int second;
            iFile >> first;
            iFile >> second;
            string line;
            int tmp = second;
            getline(iFile,line);
            cout << line;
            while(getline(iFile, line))
            {
                if(line.at(0) == '=')
                    break;
                second = tmp;
                for(int j = 0 ; j < line.length() ; j ++)
                {
                    if(line.at(j) == '1')
                        room[first][second] = -3;
                    second ++;
                }
                first ++;
            }
        }
        for(int i = 0 ; i < numberOfPaintSpills ; i ++)
        {
            int first;
            int second;
            iFile >> first;
            iFile >> second;
            paintSpillCoords.push_back(pair<int , int>(first , second));
        }
    }
}
ReaderForTnJ::~ReaderForTnJ()
{
    for(int i = 0 ; i < roomSize.second ; i++)
        delete[] room[i];
    delete[] room;
}
ReaderForTnJ::ReaderForTnJ(ReaderForTnJ & r)
{
    myCopy(r);
}
ReaderForTnJ & ReaderForTnJ::operator=(ReaderForTnJ & r)
{
    if(this != &r)
        myCopy(r);
    return *this;
}
void ReaderForTnJ::createRoom()
{
    room = new int*[roomSize.second];
    for(int i = 0 ; i < roomSize.second ; i ++)
        room[i] = new int[roomSize.first];
}
void ReaderForTnJ::fillRoomWithZero()
{
    for(int i = 0 ; i < roomSize.first ; i ++)
        for(int j = 0 ; j < roomSize.second ; j ++)
            room[i][j] = 0;
}
