#include "../include/cell.hpp"

// Constructors
Cell::Cell(int w, int h)
{
    setPos(w,h);
    setVisited(false);
}

// Setters
void Cell::setPos(int w, int h)
{
    posW=w;
    posH=h;
}
void Cell::setVisited(bool b)
{
    visited=b;
}

// Getters
int Cell::getWidthPos()
{
    return posW;
}
int Cell::getHeightPos()
{
    return posH;
}
int Cell::getUVneighboursSize()
{
    return UVneighbours.size();
}
int Cell::getVneighboursSize()
{
    return Vneighbours.size();
}
int Cell::getNextWpos(int a)
{
    return UVneighbours.at(a).getWidthPos();
}
int Cell::getNextHpos(int a)
{
    return UVneighbours.at(a).getHeightPos();
}
int Cell::getNextVWpos(int a)
{
    return Vneighbours.at(a).getWidthPos();
}
int Cell::getNextVHpos(int a)
{
    return Vneighbours.at(a).getHeightPos();
}
bool Cell::getVisited()
{
    return visited;

}

// Methods
void Cell::addUVNeighbours(int w, int h)
{
    Cell cell(w,h);
    UVneighbours.insert(std::pair<int,Cell>(UVneighbours.size(),cell));
}
void Cell::addVNeighbours(int w, int h)
{
    Cell cell(w,h);
    Vneighbours.insert(std::pair<int,Cell>(UVneighbours.size(),cell));
}

void Cell::removeUVNeighbours(int index)
{
    UVneighbours.erase(index);
}

bool Cell::checkMapEmpty()
{
    return UVneighbours.empty();
}

void Cell::clearMap()
{
    UVneighbours.clear();
}

std::string Cell::toString()
{
    return

    "W="
    + std::to_string(posW)
    + ", H="
    + std::to_string(posH )
    + ", visited="
    + std::to_string(visited);


}
