// if cell.hpp hasn't been included yet...
#ifndef __CELL_HPP_INCLUDED__
//   #define this so the compiler knows it has been included
#define __CELL_HPP_INCLUDED__

// Included dependencies
#include <map>
#include <iostream>


// the actual class
class Cell
{
    private:
        int posW;
        int posH;
        bool visited;

        std::map<int, Cell> UVneighbours;
        std::map<int, Cell> Vneighbours;

    public:
        // Constructors
        Cell(int w, int h);

        // Setters
        void setPos(int w, int h);
        void setVisited(bool b);

        // Getters
        int getWidthPos();
        int getHeightPos();
        int getUVneighboursSize();
        int getVneighboursSize();
        int getNextWpos(int a);
        int getNextHpos(int a);
        int getNextVWpos(int a);
        int getNextVHpos(int a);
        bool getVisited();

        // Methods
        void addUVNeighbours(int w, int h);
        void addVNeighbours(int w, int h);
        void removeUVNeighbours(int);
        bool checkMapEmpty();
        void clearMap();
        std::string toString();

};

// __CELL_H_INCLUDED__
#endif
