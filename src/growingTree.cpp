#include "../include/growingTree.hpp"

// Setters
void GrowingTree::setSeed(int seedChosen)
{
    seed=seedChosen;
}
void GrowingTree::setGridWidth(int width)
{
    gridWidth=width;
}
void GrowingTree::setGridHeight(int height)
{
    gridHeight=height;
}
void GrowingTree::setRandom(int seed)
{
    random.seed(seed);
}
void GrowingTree::setAmountofEdges(int amount)
{
    amountOfEdges=amount;
}

void GrowingTree::setGrid( std::vector< std::vector<Cell> > &grid )
{
    this->grid=grid;
}

void GrowingTree::setEdges(std::vector<Edge> &edges )
{
    this->edges=edges;
}
void GrowingTree::setPathEdges( std::vector<Edge> &edges )
{
    this->pathEdges=edges;
}

// Getters
int GrowingTree::getGridHeight()
{
    return gridHeight;
}
int GrowingTree::getGridWidth()
{
    return gridWidth;
}
int GrowingTree::getSeed()
{
    return seed;
}


// Methods --> functions to help initialise the maze for generating
void GrowingTree::initCells( std::vector< std::vector<Cell> > &grid )
{
    // std::cout << "initialise cells" << std::endl;
    for(int h = 0; h < getGridHeight(); h++)
    {
        std::vector<Cell> newColumn;
        for(int w = 0; w < getGridWidth(); w++)
        {
            Cell newCell(w,h);
            newColumn.push_back(newCell);
        }
        grid.push_back(newColumn);

    }
}
void GrowingTree::pickStart( int &currentPosW, int &currentPosH )
{
    // std::cout << "pick start" << std::endl;
    std::uniform_int_distribution<> rangeW(0,getGridWidth()-1);
    std::uniform_int_distribution<> rangeH(0,getGridHeight()-1);
    currentPosW=rangeW(random);
    currentPosH=rangeH(random);

    // std::cout << "start W :" << currentPosW << std::endl
    //           << "start H : " << currentPosH << std::endl;

}

// Methods --> loading Maze
void GrowingTree::loadMaze( std::string filename )
{
    std::cout << "load maze from binary file : " << filename << std::endl;

    std::ifstream inputFile(filename, std::ios::binary);

    std::vector<uint32_t> fileData;
    if( inputFile.is_open() )
    {
        while (!inputFile.eof())
        {
            uint32_t a;
            inputFile.read(reinterpret_cast<char *>(&a), sizeof(a));
            fileData.push_back(a);
        }
    }
    else
    {
        std::cout << "file couldn't open..." << std::endl;
    }

    GrowingTree maze;
    maze.setGridWidth(fileData[0]);
    maze.setGridHeight(fileData[1]);
    maze.setAmountofEdges(0);

    for(int i = 3; i < fileData.size()-3; i+=4)
    {
        Edge newEdge(fileData[i],fileData[i+1],fileData[i+2],fileData[i+3]);
        edges.push_back(newEdge);
        amountOfEdges++;
    }
}

// Methods --> saving Maze
void GrowingTree::saveMazeBinary( std::string filename )
{
    std::cout << "saving Binary file..." << std::endl;

    std::ofstream outputfile(filename, std::ios::binary);
    if (outputfile.is_open())
    {
        outputfile.write( reinterpret_cast<char*> (&gridWidth), sizeof(unsigned int) );
        outputfile.write( reinterpret_cast<char*> (&gridHeight), sizeof(unsigned int) );
        outputfile.write( reinterpret_cast<char*> (&amountOfEdges), sizeof(unsigned int) );
        for ( Edge &e : edges )
        {
            int cellAX = e.getCellAW();
            int cellAY = e.getCellAH();
            int cellBX = e.getCellBW();
            int cellBY = e.getCellBH();
            outputfile.write(reinterpret_cast<char*> (&cellAX), sizeof(unsigned int) );
            outputfile.write(reinterpret_cast<char*> (&cellAY), sizeof(unsigned int) );
            outputfile.write(reinterpret_cast<char*> (&cellBX), sizeof(unsigned int) );
            outputfile.write(reinterpret_cast<char*> (&cellBY), sizeof(unsigned int) );
        }
        outputfile.close();
    }
}
/**
    print the white grid
    get direction of edge
    print black line depending of direction
**/
void GrowingTree::saveMazeSVG( std::string filename )
{
    std::cout << "saving SVG..." << std::endl;
    // std::cout << "amount of edges: " << edges.size() << std::endl;

    std::ofstream ofs (filename, std::ofstream::out);
    ofs << "<svg width='" << getGridWidth() * MAZE_AMPL << "' height='" << getGridHeight() * MAZE_AMPL << "' xmlns='http://www.w3.org/2000/svg'>" << std::endl;
    ofs << "  <rect x='0' y='0' width='" << getGridWidth() * MAZE_AMPL << "' height='" << getGridHeight() * MAZE_AMPL << "' style='fill:black; stroke-width:0; opacity:1' />" << std::endl;
    printGrid(ofs,getGridWidth(),getGridHeight());
    for (Edge e : edges)
    {
        printWall(ofs, e, getDirection(e));
    }

    ofs << "</svg>" << std::endl;
    ofs.close();

}
void GrowingTree::printGrid(std::ofstream& file, int width, int height)
{
    // std::cout << "printing grid..." << std::endl;

    // prints rows
    for(int i =0; i <height;i++)
    {
        file
        << "   <line x1=\"" <<  0 * MAZE_AMPL << "\" y1=\"" <<  i * MAZE_AMPL
        << "\" x2=\"" <<  width * MAZE_AMPL << "\" y2=\"" <<  i * MAZE_AMPL
        << "\" style=\"stroke:rgb(255,255,255);stroke-width:1\" />"
        << std::endl;
    }
    // prints columns
    for(int j =0; j<width; j++)
    {
        file
        << "   <line x1=\"" <<  j * MAZE_AMPL << "\" y1=\"" <<  0 * MAZE_AMPL
        << "\" x2=\"" <<  j * MAZE_AMPL << "\" y2=\"" <<  height * MAZE_AMPL
        << "\" style=\"stroke:rgb(255,255,255);stroke-width:1\" />"
        << std::endl;
    }
}
// 0,0 is the top left position,
// with x increasing the the right
// and y increasing down
Direction GrowingTree::getDirection(Edge e)
{
    // std::cout << "getting direction" << std::endl;

    Direction d = ERROR;
    if( e.getCellAW()==e.getCellBW() && e.getCellAH()>e.getCellBH() )
    {
        d= NORTH;
        return d;
    }
    else if( e.getCellAW()==e.getCellBW() && e.getCellAH()<e.getCellBH() )
    {
        d= SOUTH;
        return d;
    }
    else if( e.getCellAW()>e.getCellBW() && e.getCellAH()==e.getCellBH() )
    {
        d= WEST;
        return d;

    }
    else if( e.getCellAW()<e.getCellBW() && e.getCellAH()==e.getCellBH() )
    {
        d= EAST;
        return d;

    }
    else
    {
        std::cout << "this edge doesn't move in an allowed direction" << std::endl;
        return d;

    }
}
void GrowingTree::printWall(std::ofstream& file, Edge e, Direction d)
{
    if( d == NORTH )
    {
        file    << "    <line x1=\"" << (e.getCellAW()) * MAZE_AMPL
                << "\" y1=\"" << (e.getCellAH()) * MAZE_AMPL
                << "\" x2=\"" << (e.getCellAW()+1) * MAZE_AMPL
                << "\" y2=\"" << (e.getCellAH()) * MAZE_AMPL
                << "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />"
                << std::endl;

    }
    else if( d == EAST )
    {
        file    << "    <line x1=\"" << (e.getCellBW()) * MAZE_AMPL
                << "\" y1=\"" << (e.getCellBH()) * MAZE_AMPL
                << "\" x2=\"" << (e.getCellBW()) * MAZE_AMPL
                << "\" y2=\"" << (e.getCellBH()+1) * MAZE_AMPL
                << "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />"
                << std::endl;
    }
    else if( d == SOUTH )
    {
        file    << "    <line x1=\"" << (e.getCellBW()) * MAZE_AMPL
                << "\" y1=\"" << (e.getCellBH()) * MAZE_AMPL
                << "\" x2=\"" << (e.getCellBW()+1) * MAZE_AMPL
                << "\" y2=\"" << (e.getCellBH())* MAZE_AMPL
                << "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />"
                << std::endl;
    }
    else if( d == WEST )
    {
        file    << "    <line x1=\"" << (e.getCellAW()) * MAZE_AMPL
                << "\" y1=\"" <<( e.getCellAH()) * MAZE_AMPL
                << "\" x2=\"" << (e.getCellAW()) * MAZE_AMPL
                << "\" y2=\"" << (e.getCellAH()+1) * MAZE_AMPL
                << "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />"
                << std::endl;
    }
    else
    {
        std::cout << "invaild direction, nothing to print..." << std::endl;
    }
}

// Methods --> finding path

/**
    searchs for path by first trying to go south, then east, west finally north
    as long as the last direction moved wasnt the oposite,
    since you would have just come from there
**/
void GrowingTree::findPath( int gridw, int gridh, std::string filename )
{

    std::cout << "Solving Path" << std::endl;
    std::cout << "  trying to get to : (" << gridh-1 << "," << gridw-1 << ")"<< std::endl;

    // add start time
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    Direction lastDirection = ERROR;
    Direction currentDirection = ERROR;
    int currentPosW =0;
    int currentPosH=0;

    // if maze can be solved or not
    // use this to determine if you need to print path at end
    bool foundPath = false;

    // find 0,0 and add to set
    if ( findPathStart(currentPosW,currentPosH,lastDirection) == false )
    {
        std::cout << "  no edge at point (0,0) " << std::endl;
    }
    else
    {
        std::cout << "  edge found at point (0,0) " << std::endl;

    }


    // from starting postion (0,0) look for edges down to point
    // (height-1,width-1)
    while ( path.size() > 0) //   && a < 10
    {
        currentPosW = path.back().first.getWidthPos();
        currentPosH = path.back().first.getHeightPos();
        // check if we solved maze
        if( currentPosW==gridw-1 && currentPosH==gridh-1 )
        {
            // path has been found
            foundPath = true;
            break;
        }
        else
        {
            // std::cout << "  still finding path..." << std::endl;
        }
        // check there is a direction we can search
        while ( path.back().second.size() > 0 )
        {
            // get direction and remove so its not searched again
            currentDirection = path.back().second.front();
            // find the next postion
            if( findEdge(currentPosW,currentPosH, currentDirection) )
            {
                // start outer loop again
                break;
            }
            else
            {
                // remove this direction
                path.back().second.pop();
                // check if the postion has any more directions to go to
                if ( path.back().second.size() == 0 )
                {
                    // add this cell loaction as a visited cell to stop revisting
                    visitedCell.push_back(Cell(currentPosW,currentPosH));
                    // no posible directions, remove from deque
                    path.pop_back();
                    break;
                }
            }
        }
    }

    //check if we need to print solution
    if (foundPath == true )
    {
        // add end time
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        // calculate generating time and print
        std::cout << "Maze generating took "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
                  << "us. ("
                  << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
                  << " seconds)\n";

        std::cout << "  path found, printing solution..." << std::endl;
        // using the path list make edges to each point
        createPathEdges();
        // print path
        savePathSVG(filename);
    }
    else
    {
        std::cout << "  no path found..." << std::endl;
    }

}

bool GrowingTree::findPathStart(int cw, int ch, Direction lastDir)
{
    // std::cout << "  finding start " << std::endl;

    for(Edge e : edges)
    {
        if( e.getCellAW() == cw && e.getCellAH() == ch)
        {
            // add this postion to the stack
            loadDirection(cw,ch,lastDir);
            // no need to search the list of edges anymore
            return true;
        }
        if( e.getCellBW()== cw && e.getCellBH() == ch)
        {
            // add this postion to the stack
            loadDirection(cw,ch,lastDir);
            return true;
        }
    }
    // if here there is on point 0,0 in the list of edges
    return false;
}

/*
    load directions opposite to last moved
    since queue add south, east, west then north
*/
void GrowingTree::loadDirection(int cw, int ch, Direction lastDir)
{
    // std::cout << "loading directions for current point" << std::endl;
    if( lastDir == ERROR )
    {
        // std::cout << "          loaded: south and east" << std::endl;

        // this will be a start postion, probably point 0,0
        // only need to load the south and east position
        Cell newCell(cw,ch);
        std::queue<Direction> newQueue;
        Direction south=SOUTH;
        Direction east=EAST;
        newQueue.push(south);
        newQueue.push(east);
        path.push_back( std::pair< Cell, std::queue<Direction> >(newCell, newQueue ) );
    }
    else if( lastDir == SOUTH )
    {
        // std::cout << "          loaded: south, east, west" << std::endl;

        // if moved south load all directions besides NORTH
        Cell newCell(cw,ch);
        std::queue<Direction> newQueue;
        Direction south=SOUTH;
        Direction east=EAST;
        Direction west=WEST;
        newQueue.push(south);
        newQueue.push(east);
        newQueue.push(west);

        path.push_back( std::pair< Cell, std::queue<Direction> >(newCell, newQueue ) );
    }
    else if( lastDir == EAST )
    {
        // std::cout << "          loaded: south, east, north" << std::endl;

        // add south, east and north
        Cell newCell(cw,ch);
        std::queue<Direction> newQueue;
        Direction south=SOUTH;
        Direction east=EAST;
        Direction north=NORTH;
        newQueue.push(south);
        newQueue.push(east);
        newQueue.push(north);

        path.push_back( std::pair< Cell, std::queue<Direction> >(newCell, newQueue ) );
    }
    else if( lastDir == WEST )
    {
        // std::cout << "          loaded: south, west, north" << std::endl;

         // add south,west,north
         Cell newCell(cw,ch);
         std::queue<Direction> newQueue;
         Direction south=SOUTH;
         Direction west=WEST;
         Direction north=NORTH;
         newQueue.push(south);
         newQueue.push(west);
         newQueue.push(north);

         path.push_back( std::pair< Cell, std::queue<Direction> >(newCell, newQueue ) );
    }
    else if( lastDir == NORTH )
    {
        // std::cout << "          loaded: east, west, north" << std::endl;

        // add, east,west, north
        Cell newCell(cw,ch);
        std::queue<Direction> newQueue;
        Direction east=EAST;
        Direction west=WEST;
        Direction north=NORTH;
        newQueue.push(east);
        newQueue.push(west);
        newQueue.push(north);

        path.push_back( std::pair< Cell, std::queue<Direction> >(newCell, newQueue ) );
    }
}

bool GrowingTree::findEdge(int cw, int ch, Direction currDir)
{
    // std::cout << "      finding edge" << std::endl;

    int nw;
    int nh;
    // get position of the direction we want to go to
    getNext(cw,ch,nw,nh,currDir);

    // search list of edges for an edge that has both the current and next points
    for ( Edge e : edges )
    {
        if ( (e.getCellAW() == cw && e.getCellAH() == ch) )
        {
            if ( e.getCellBW() == nw && e.getCellBH() == nh)
            {
                // check if this next cell has already been visited
                for(Cell c : visitedCell )
                {
                    if( c.getWidthPos() == nw && c.getHeightPos() == nh )
                    {
                        // been visited
                        return false;
                    }
                }
                // add the next position to the stack
                loadDirection(nw,nh,currDir);
                return true;
            }
        }
        else if( e.getCellAW() == nw && e.getCellAH() == nh )
        {
            if( e.getCellBW() == cw && e.getCellBH() == ch )
            {
                // add the next position to the stack

                // check if this next cell has already been visited
                for(Cell c : visitedCell )
                {
                    if( c.getWidthPos() == nw && c.getHeightPos() == nh )
                    {
                        // been visited
                        return false;
                    }
                }

                loadDirection(nw,nh,currDir);
                return true;
            }
        }
    }

    return false;

}
void GrowingTree::getNext(int cw, int ch, int &nw, int &nh, Direction d)
{
    // std::cout << "          getting next direction" << std::endl;
    if(d==ERROR)
    {
        // std::cout << "              next is same postion" << std::endl;
        nw=cw;
        nh=ch;
    }
    else if(d==SOUTH)
    {
        // std::cout << "              next is south postion" << std::endl;
        nw=cw;
        nh=ch+1;
    }
    else if(d==EAST)
    {
        // std::cout << "              next is east postion" << std::endl;
        nw=cw+1;
        nh=ch;
    }
    else if( d == WEST )
    {
        // std::cout << "              next is west postion" << std::endl;
        nw=cw-1;
        nh=ch;
    }
    else if( d==NORTH )
    {
        // std::cout << "              next is north postion" << std::endl;
        nw=cw;
        nh=ch-1;
    }
    else
    {
        // error
    }
}

bool GrowingTree::pointExist(int nw, int nh)
{
    // std::cout << "checking if we have already been to this point" << std::endl;

    for( std::pair< Cell, std::queue<Direction> > p : path )
    {
        if( path.back().first.getWidthPos() == nw &&
            path.back().first.getHeightPos() == nh )
        {
            // std::cout << "cell been visited" << std::endl;
            return true;
        }
    }

    return false;
}

void GrowingTree::createPathEdges()
{
    for(int i=0; i<path.size()-1; i++)
    {

        Edge newEdge(path[i].first.getWidthPos(), path[i].first.getHeightPos(),
                     path[i+1].first.getWidthPos(), path[i+1].first.getHeightPos() );
        pathEdges.push_back(newEdge);

    }
}

void GrowingTree::savePathSVG( std::string filename )
{
    std::cout << "saving Path..." << std::endl;

    std::ofstream ofs (filename, std::ofstream::out);
    ofs << "<svg width='" << getGridWidth() * MAZE_AMPL << "' height='" << getGridHeight() * MAZE_AMPL << "' xmlns='http://www.w3.org/2000/svg'>" << std::endl;
    ofs << "  <rect x='0' y='0' width='" << getGridWidth() * MAZE_AMPL << "' height='" << getGridHeight() * MAZE_AMPL << "' style='fill:black; stroke-width:0; opacity:1' />" << std::endl;
    printGrid(ofs,getGridWidth(),getGridHeight());
    for (Edge e : edges)
    {
        printWall(ofs, e, getDirection(e));
    }
    for( Edge e : pathEdges)
    {
        printPath(ofs,e,getDirection(e));
    }


    ofs << "</svg>" << std::endl;
    ofs.close();
}
void GrowingTree::printPath(std::ofstream& file, Edge e, Direction d)
{
    if( d == NORTH )
    {
        file    << "    <line x1=\"" << (e.getCellAW()+0.5) * MAZE_AMPL
                << "\" y1=\"" << (e.getCellAH()+0.5) * MAZE_AMPL
                << "\" x2=\"" << (e.getCellBW()+0.5) * MAZE_AMPL
                << "\" y2=\"" << (e.getCellBH()+0.5) * MAZE_AMPL
                << "\" style=\"stroke:rgb(255,0,0);stroke-width:0.5\" />"
                << std::endl;

    }
    else if( d == EAST )
    {
        file    << "    <line x1=\"" << (e.getCellAW()+0.5) * MAZE_AMPL
                << "\" y1=\"" << (e.getCellAH()+0.5) * MAZE_AMPL
                << "\" x2=\"" << (e.getCellBW()+0.5) * MAZE_AMPL
                << "\" y2=\"" << (e.getCellBH()+0.5) * MAZE_AMPL
                << "\" style=\"stroke:rgb(255,0,0);stroke-width:.5\" />"
                << std::endl;
    }
    else if( d == SOUTH )
    {
        file    << "    <line x1=\"" << (e.getCellAW()+0.5) * MAZE_AMPL
                << "\" y1=\"" << (e.getCellAH()+0.5) * MAZE_AMPL
                << "\" x2=\"" << (e.getCellBW()+0.5) * MAZE_AMPL
                << "\" y2=\"" << (e.getCellBH()+0.5)* MAZE_AMPL
                << "\" style=\"stroke:rgb(255,0,0);stroke-width:0.5\" />"
                << std::endl;
    }
    else if( d == WEST )
    {
        file    << "    <line x1=\"" << (e.getCellAW()+0.5) * MAZE_AMPL
                << "\" y1=\"" <<( e.getCellAH()+0.5) * MAZE_AMPL
                << "\" x2=\"" << (e.getCellBW()+0.5) * MAZE_AMPL
                << "\" y2=\"" << (e.getCellBH()+0.5) * MAZE_AMPL
                << "\" style=\"stroke:rgb(255,0,0);stroke-width:0.5\" />"
                << std::endl;
    }
    else
    {
        std::cout << "invaild direction, nothing to print..." << std::endl;
    }
}
