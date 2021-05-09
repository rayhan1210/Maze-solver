#include "../include/prim.hpp"

// Constructors
Prim::Prim()
{
    setSeed(DEFAULT_SEED);
    setGridWidth(DEFAULT_WIDTH);
    setGridHeight(DEFAULT_HEIGHT);
    setAmountofEdges(INIT_EDGE);
    setRandom( getSeed() );
    initCells(grid);

}
Prim::Prim(int seed)
{
    setSeed(seed);
    setGridWidth(DEFAULT_WIDTH);
    setGridHeight(DEFAULT_HEIGHT);
    setAmountofEdges(INIT_EDGE);
    setRandom( getSeed() );
    initCells(grid);
}
Prim::Prim(int seed, int width, int height)
{
    setSeed(seed);
    setGridWidth(width);
    setGridHeight(height);
    setAmountofEdges(INIT_EDGE);
    setRandom( getSeed() );
    initCells(grid);
}

// Setters
void Prim::setSeed(int seedChosen)
{
    seed=seedChosen;
}
void Prim::setGridWidth(int width)
{
    gridWidth=width;
}
void Prim::setGridHeight(int height)
{
    gridHeight=height;
}
void Prim::setRandom(int seed)
{
    random.seed(seed);
}
void Prim::setAmountofEdges(int amount)
{
    amountOfEdges=amount;
}

// Getters
int Prim::getGridHeight()
{
    return gridHeight;
}
int Prim::getGridWidth()
{
    return gridWidth;
}
int Prim::getSeed()
{
    return seed;
}

// Methods --> Generating maze
void Prim::generateMaze()
{
    std::cout << "generating maze" << std::endl;
    // add start time
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    // start maze generating
    pickStart(currentPosW, currentPosW );

    // sets this cell to visited
    grid[currentPosH][currentPosW].setVisited(true);

    // set the current index
    currentIndex = listOfCells.size();

    // add this cell of list of cells
    listOfCells.push_back(grid[currentPosH][currentPosW]);

    while( (listOfCells.size() > 0) )
    {
        // std::cout << "list size : "  << listOfCells.size() << std::endl;
        walk();
    }
    // maze generating done

    // add end time
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    // calculate generating time and print
    std::cout << "Maze generating took "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << "us. ("
              << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
              << " seconds)\n";

      setGrid(grid);
      setEdges(edges);

}

void Prim::walk()
{
    // clear cell map of unvisted neighbours
    grid[currentPosH][currentPosW].clearMap();
    // looks for unvisited neighbours
    findUnvisitedNeighbours();
    // if there is unvisited neighbours
    pickNext();
}

void Prim::findUnvisitedNeighbours()
{
     // std::cout << "find unvisted neighbours" << std::endl;

    if( currentPosH+1 < getGridHeight() )
    {
        if( !grid[currentPosH+1][currentPosW].getVisited() )
        {
            grid[currentPosH][currentPosW].addUVNeighbours(currentPosW,currentPosH+1);
        }
    }
    if( currentPosH-1 >= 0 )
    {
        if( !grid[currentPosH-1][currentPosW].getVisited() )
        {
            grid[currentPosH][currentPosW].addUVNeighbours(currentPosW,currentPosH-1);
        }
    }
    if( currentPosW+1 < getGridWidth())
    {
        if( !grid[currentPosH][currentPosW+1].getVisited() )
        {
            grid[currentPosH][currentPosW].addUVNeighbours(currentPosW+1,currentPosH);
        }
    }
    if( currentPosW-1 >= 0)
    {
        if( !grid[currentPosH][currentPosW-1].getVisited() )
        {
            grid[currentPosH][currentPosW].addUVNeighbours(currentPosW-1,currentPosH);
        }
    }
}

void Prim::pickNext()
{
    if( grid[currentPosH][currentPosW].getUVneighboursSize() >  0 )
    {
        // makes range to pick from
        std::uniform_int_distribution<> pickNeighbour(0, grid[currentPosH][currentPosW].getUVneighboursSize()-1);
        // chooses a random neighbour
        int nextCell = pickNeighbour(random);
        //gets next cell location
        nextPosW = grid[currentPosH][currentPosW].getNextWpos(nextCell);
        nextPosH = grid[currentPosH][currentPosW].getNextHpos(nextCell);


        // makes an edge between the cells
        Edge newEdge(currentPosW,currentPosH,nextPosW,nextPosH);
        edges.push_back(newEdge);
        amountOfEdges++;


        // add this new cell to the list of cells
        listOfCells.push_back( grid[nextPosH][nextPosW]) ;
        // sets this cell to visited
        grid[nextPosH][nextPosW].setVisited(true);

        if( listOfCells.size() > 0 )
        {
            // pick next cell to search from
            std::uniform_int_distribution<> pickNextToSearch(0, listOfCells.size() -1);
            currentIndex = pickNextToSearch(random);
            // gets next cell location
            currentPosW = listOfCells[currentIndex].getWidthPos();
            currentPosH = listOfCells[currentIndex].getHeightPos();
        }
     }
     else
     {
         // if this cell has no unvisited neighbours,
         // remove from the list and check the previous cell
         if( listOfCells.size() > 0 )
         {
             listOfCells.erase(listOfCells.begin()+currentIndex);

             if( listOfCells.size() > 0 )
             {
                 // pick next cell to search from
                 std::uniform_int_distribution<> pickNextToSearch(0, listOfCells.size() -1);
                 currentIndex = pickNextToSearch(random);
                 // gets next cell location
                 currentPosW = listOfCells[currentIndex].getWidthPos();
                 currentPosH = listOfCells[currentIndex].getHeightPos();
             }
         }
     }
}
