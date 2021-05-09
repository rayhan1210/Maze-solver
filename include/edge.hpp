// edge.hpp

// if edge.hpp hasn't been included yet...
#ifndef __EDGE_HPP_INCLUDED__
//   #define this so the compiler knows it has been included
#define __EDGE_HPP_INCLUDED__

// the actual class
class Edge
{
    private:
        int CellAW;
        int CellAH;
        int CellBW;
        int CellBH;

    public:
        // Constructors
        Edge(int w1, int h1, int w2, int h2);

        // Setters
        void setCellA(int w, int  h);
        void setCellB(int  w, int h);

        // Getters
        int getCellAW();
        int getCellAH();
        int getCellBW();
        int getCellBH();

};

// __EDGE_H_INCLUDED__
#endif
