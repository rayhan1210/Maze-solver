// if RecursiveBackTracker.hpp hasn't been included yet...
#ifndef __RECURSIVEBACKTRACKER_HPP_INCLUDED__
//   #define this so the compiler knows it has been included
#define __RECURSIVEBACKTRACKER_HPP_INCLUDED__

// Included dependencies
#include "growingTree.hpp"

// Class definition
class RecursiveBackTracker : public GrowingTree
{
    private:

        // class variables
        int seed;
        int gridWidth;
        int gridHeight;
        int currentPosW;
        int currentPosH;
        int nextPosW;
        int nextPosH;
        int amountOfEdges;
        std::mt19937 random;

        std::vector<Edge> edges;
        std::vector< std::vector<Cell> > grid;
        std::stack<Cell> listOfCells;

    public:
        // Constructors
        RecursiveBackTracker();
        RecursiveBackTracker(int);
        RecursiveBackTracker(int, int, int);

        // Setters
        void setSeed(int);
        void setGridWidth(int);
        void setGridHeight(int);
        void setRandom(int);
        void setAmountofEdges(int);


        // Getters
        int getGridHeight();
        int getGridWidth();
        int getSeed();

        // Methods --> Generating maze
        void generateMaze();
        void walk();
        void findUnvisitedNeighbours();
        void pickNext();

};

// __RecursiveBackTracker_H_INCLUDED__
#endif
