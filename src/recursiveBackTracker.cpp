#include "../include/recursiveBackTracker.hpp"

// Constructors
RecursiveBackTracker::RecursiveBackTracker()
{
    setSeed(DEFAULT_SEED);
    setGridWidth(DEFAULT_WIDTH);
    setGridHeight(DEFAULT_HEIGHT);
    setAmountofEdges(INIT_EDGE);
    setRandom( getSeed() );
    initCells(grid);

}
RecursiveBackTracker::RecursiveBackTracker(int seed)
{
    setSeed(seed);
    setGridWidth(DEFAULT_WIDTH);
    setGridHeight(DEFAULT_HEIGHT);
    setAmountofEdges(INIT_EDGE);
    setRandom( getSeed() );
    initCells(grid);
}
RecursiveBackTracker::RecursiveBackTracker(int seed, int width, int height)
{
    setSeed(seed);
    setGridWidth(width);
    setGridHeight(height);
    setAmountofEdges(INIT_EDGE);
    setRandom( getSeed() );
    initCells(grid);
}

// Setters
void RecursiveBackTracker::setSeed(int seedChosen)
{
    seed=seedChosen;
}
void RecursiveBackTracker::setGridWidth(int width)
{
    gridWidth=width;
}
void RecursiveBackTracker::setGridHeight(int height)
{
    gridHeight=height;
}
void RecursiveBackTracker::setRandom(int seed)
{
    random.seed(seed);
}
void RecursiveBackTracker::setAmountofEdges(int amount)
{
    amountOfEdges=amount;
}

// Getters
int RecursiveBackTracker::getGridHeight()
{
    return gridHeight;
}
int RecursiveBackTracker::getGridWidth()
{
    return gridWidth;
}
int RecursiveBackTracker::getSeed()
{
    return seed;
}

// Methods --> Generating maze
void RecursiveBackTracker::generateMaze()
{
    std::cout << "generating maze" << std::endl;
    // add start time
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    // start maze generating
    pickStart(currentPosW, currentPosW );
    walk();
    while( (listOfCells.size() > 0) )
    {
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

void RecursiveBackTracker::walk()
{
    // sets this cell to visited
    grid[currentPosH][currentPosW].setVisited(true);

    // clear cell map of unvisted neighbours
    grid[currentPosH][currentPosW].clearMap();
    // looks for unvisited neighbours
    findUnvisitedNeighbours();

    // if there is unvisited neighbours
    pickNext();


}
void RecursiveBackTracker::findUnvisitedNeighbours()
{
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
void RecursiveBackTracker::pickNext()
{
    if( grid[currentPosH][currentPosW].getUVneighboursSize() >  0 )
    {
        // push this cell to the stack since we need to finf the next cell
        listOfCells.push( grid[currentPosH][currentPosW] );

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
        // before moving to next cell remove next chosen cell from unvisited list in current cell
        if( !grid[currentPosH][currentPosW].checkMapEmpty() )
        {
            grid[currentPosH][currentPosW].removeUVNeighbours(nextCell);
        }
        // move to the neighbouring cell
        currentPosW = nextPosW;
        currentPosH = nextPosH;
        // call walk again
        walk();
     }
     else
     {
         // if this cell has no unvisited neighbours,
         // remove from the list and check the previous cell
         if( listOfCells.size() > 0 )
         {
             listOfCells.pop();
             if( listOfCells.size() > 0 )
             {
                 currentPosW = listOfCells.top().getWidthPos();
                 currentPosH = listOfCells.top().getHeightPos();
             }
         }
     }
}
