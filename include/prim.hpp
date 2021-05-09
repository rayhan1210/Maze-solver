// if growingTree.hpp hasn't been included yet...
#ifndef __PRIM_HPP_INCLUDED__
//   #define this so the compiler knows it has been included
#define __PRIM_HPP_INCLUDED__

// Included dependencies
#include "growingTree.hpp"
#include <deque>

// Class definition
class Prim : public GrowingTree
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
        int currentIndex;
        std::deque<Cell> listOfCells;

    public:
        // Constructors
        Prim();
        Prim(int);
        Prim(int, int, int);

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

// __GROWINGTREE_H_INCLUDED__
#endif
