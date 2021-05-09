#include "../include/edge.hpp"

// Constructors
Edge::Edge(int w1, int h1, int w2, int h2)
{
    setCellA(w1,h1);
    setCellB(w2,h2);
}

// Setters
void Edge::setCellA(int w, int  h)
{
    CellAW = w;
    CellAH = h;
}
void Edge::setCellB(int  w, int h)
{
    CellBW = w;
    CellBH = h;
}

// Getters
int Edge::getCellAW()
{
    return CellAW;
}
int Edge::getCellAH()
{
    return CellAH;
}
int Edge::getCellBW()
{
    return CellBW;
}
int Edge::getCellBH()
{
    return CellBH;
}
