// if maze.hpp hasn't been included yet...
#ifndef __GROWINGTREE_HPP_INCLUDED__
//   #define this so the compiler knows it has been included
#define __GROWINGTREE_HPP_INCLUDED__

// Included dependencies
#include "../include/cell.hpp"
#include "../include/edge.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>
#include <memory>
#include <stack>
#include <queue>
#include <utility>

// Defining constant values
const int DEFAULT_SEED = 1;
const int DEFAULT_WIDTH = 3;
const int DEFAULT_HEIGHT = 3;
const int INIT_EDGE = 0;
const int MAZE_AMPL = 10; // for increasing the size for the maze for saving

const int START_W = 0;
const int START_H = 0;

enum Direction
{
    ERROR,
    NORTH,
    EAST,
    SOUTH,
    WEST
};

// Class definition
class GrowingTree
{

    private:
        // class variables
        int seed;
        int gridWidth;
        int gridHeight;
        int amountOfEdges;
        std::mt19937 random;
        // Maze generation containers
        std::vector<Edge> edges;
        std::vector< std::vector<Cell> > grid;
        // this container keeps track of what cell we are at
        // and where to search for next postion
        std::deque< std::pair< Cell, std::queue<Direction> > > path;
        // when poping from path need to record that popped cell to you dont revist it
        std::deque< Cell > visitedCell;
        // once path is found make a list of edges to print
        std::vector<Edge> pathEdges;

    public:

        // Setters
        virtual void setSeed(int);
        virtual void setGridWidth(int);
        virtual void setGridHeight(int);
        virtual void setRandom(int);
        virtual void setAmountofEdges(int);

        void setGrid( std::vector< std::vector<Cell> > &grid );
        void setEdges( std::vector<Edge> &edges );
        void setPathEdges( std::vector<Edge> &edges );
        // Getters
        virtual int getGridHeight();
        virtual int getGridWidth();
        virtual int getSeed();

        // Methods --> functions to help initise the maze for generating
        void initCells( std::vector< std::vector<Cell> > & );
        void pickStart( int &, int & );

        // Methods --> loading Maze
        void loadMaze( std::string );

        // Methods --> saving Maze
        void saveMazeBinary( std::string );
        void saveMazeSVG( std::string );
        void printGrid(std::ofstream& file, int width, int height);
        Direction getDirection(Edge e);
        void printWall(std::ofstream& file, Edge e, Direction d);

        // Methods --> finding Path
        void findPath( int,int,std::string );
        bool findPathStart(int,int,Direction);
        void loadDirection(int,int,Direction);
        bool findEdge(int, int, Direction);
        void getNext(int, int, int &, int &, Direction);
        bool pointExist(int w, int h);
        // Methods --> saving Path
        void createPathEdges();
        void savePathSVG( std::string filename );
        void printPath(std::ofstream& file, Edge e, Direction d);

};
// __MAZE_H_INCLUDED__
#endif
