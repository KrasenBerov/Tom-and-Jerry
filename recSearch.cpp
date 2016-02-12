
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <list>
#include <vector>
#define DIRF 'f'
#define DIRL 'l'
#define DIRR 'r'
#define DIRB 'b'
#define DIRN 'T'
using namespace std;
class Path
{
private:
    int startX;
    int startY;
    vector<char> steps;
    void myCopy(Path & p)
    {
        startX = p.startX;
        startY = p.startY;
        steps.clear();
        for(int i = 0 ; i < p.steps.size() ; i ++)
            steps.push_back(p.steps.at(i));
    }
public:
    void resetPath(int _x , int _y)
    {
        startX = _x;
        startY = _y;
    }
    Path(int _x , int _y)
    {
        resetPath(_x , _y);
    }
    Path(Path & p)
    {
        myCopy(p);
    }
    Path& operator=(Path & p)
    {
        if(this != &p)
            myCopy(p);
        return *this;
    }
    void addStep(char _step)
    {
        steps.push_back(_step);
    }
    int getLengthOfPath()
    {
        int br = 0;
        for(int i = 0 ; i < steps.size() ; i ++)
            if(steps.at(i) != (char)'p')
                br++;
        return (br-1);
    }
    void removeStep()
    {
        steps.pop_back();
    }
    int getNumberOfTurns()
    {
        int tmpNumberOfTurns = 0;
        vector<char> tmpSteps;
        for(int i = 0 ; i < steps.size() ; i++)
            if(steps.at(i) != 'p' && steps.at(i) != 'T')
                tmpSteps.push_back(steps.at(i));
        for(int i = 1 ; i < tmpSteps.size() ; i++)
            if(tmpSteps.at(i) != tmpSteps.at(i-1))
            tmpNumberOfTurns++;

        return tmpNumberOfTurns;
    }
    int getPaintSpills()
    {
        int br = 0;
        for(int i = 0 ; i < steps.size() ; i ++)
            if(steps.at(i) == 'p')
                 br ++;
        return br;
    }
    void printPath()
    {
        cout << "The path is " << endl;
        for(int i = 0 ; i < steps.size() ; i ++)
            cout << (steps.at(i));
        cout << endl;
        cout << "It has " << getNumberOfTurns() << " turns and " << getPaintSpills() << " paint spills." << endl;
    }

};
class Matrix
{
private:
    int DIMX , DIMY;
    int **matrix;
    Path * currentPath;
    list<Path*> paths;
    list<pair< int , int > > pickObjs;
    bool checkForObj(int _x , int _y)
    {
        pair<int , int> tmpPair;
        tmpPair.first = _x;
        tmpPair.second = _y;
        if(!pickObjs.empty())
        for(list < pair < int , int > >::iterator i = pickObjs.begin() ; i != pickObjs.end() ; i++)
            if((*i) == tmpPair)
                return true;
        return false;
    }
    void popAllPaths()
    {
        while(!paths.empty())
            paths.pop_back();
    }
    void insertNewPath(Path * p)
    {
        Path * tmp = new Path((*p));
        if(!paths.empty())
        {
            if(tmp->getLengthOfPath() < paths.back()->getLengthOfPath())
            {
                popAllPaths();
                paths.push_back(tmp);
            }
            else if(tmp->getLengthOfPath() == paths.back()->getLengthOfPath())
                    paths.push_back(tmp);
        }
        else
            paths.push_back(tmp);
    }
    void createMatrix()
    {
        matrix = new int*[DIMY];
        for(int i = 0 ; i < DIMY ; i++)
            matrix[i] = new int[DIMX];
    }
    void copyMatrix(int **_matrix)
    {
        for(int i = 0 ; i < DIMX ; i ++)
            for(int j = 0 ; j < DIMY ; j ++)
                matrix[i][j] = _matrix[i][j];
    }
public:
    Matrix()
    {
        DIMX = 0;
        DIMY = 0;
        currentPath = NULL;
        createMatrix();
    }
    Matrix(int x , int y, int ** _matrix , list<pair < int , int > > _pickObjs)
    {
        DIMX = x;
        DIMY = y;
        createMatrix();
        copyMatrix(_matrix);
        currentPath = NULL;
        pickObjs = _pickObjs;
    }
    ~Matrix()
    {
        if(currentPath != NULL)
            delete currentPath;
        if(matrix != NULL)
        {
            for(int i = 0 ; i < DIMY ; i ++)
                delete[] matrix[i];
            delete[] matrix;
        }
    }
    void printMatrix()
    {
        for(int i = 0 ; i < DIMX ; i ++)
        {
            cout << "|";
            for(int j = 0 ; j < DIMY ; j ++)
            {
                if(checkForObj(i,j))
                    cout << "P|";
                else
                    cout << (char)matrix[i][j] << "|" ;
            }
            cout << endl;
        }
    }
    Path * findPath(int topX , int topY, int endX, int endY, char dir = DIRN)
    {
        Path * resPath;//result path
        resPath = NULL;
        if(currentPath == NULL)
            currentPath = new Path ( topX , topY);
        if(topX >= 0 && topX < DIMX && topY >= 0 && topY < DIMY && matrix[topX][topY] == 0)
        {
            if(checkForObj(topX , topY))
                currentPath->addStep('p');
            if(topX == endX && topY == endY )
            {
                currentPath->addStep(dir);
                resPath = currentPath;
                insertNewPath(resPath);
                currentPath->removeStep();
            }
            else
            {
                currentPath->addStep(dir);
                matrix[topX][topY] = -5;//is checked
                Path* tmpPath;
                if(NULL != (tmpPath = findPath(topX + 1 , topY , endX , endY , DIRB)))
                    resPath = tmpPath;
                if(NULL != (tmpPath = findPath(topX - 1 , topY , endX , endY , DIRF)))
                    resPath = tmpPath;
                if(NULL != (tmpPath = findPath(topX , topY + 1 , endX , endY , DIRR)))
                    resPath = tmpPath;
                if(NULL != (tmpPath = findPath(topX , topY - 1 , endX , endY , DIRL)))
                    resPath = tmpPath;
                currentPath->removeStep();
                if(checkForObj(topX, topY))
                    currentPath->removeStep();
                matrix[topX][topY] = 0;
            }
        }
        return resPath;
    }
    int numberOfPaths()
    {
        int br = 0;
        for(list<Path*>::iterator i = paths.begin() ; i != paths.end() ; i++)
            br++;
        return br;
    }
    void printAllPaths()
    {
        cout << "The shortest paths from Tom to Jerry are " << numberOfPaths() << " and their length is " << (*paths.begin())->getLengthOfPath() << endl;
        for(list<Path*>::iterator i = paths.begin() ; i != paths.end() ; i++)
            (*i)->printPath();
    }

};
