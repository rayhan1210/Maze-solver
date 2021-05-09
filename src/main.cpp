#include "../include/growingTree.hpp"
#include "../include/prim.hpp"
#include "../include/recursiveBackTracker.hpp"
#include <stdexcept>

int main(int argc, char** argv)
{

    std::vector<std::string> args;
    for( int i =0; i<argc; i++)
    {
        args.push_back(argv[i]);
    }

    if( argc < 2 || argc > 11)
    {
        std::cout << "incorrect amount of command argument, exiting system..." << std::endl;
        return 0;
    }

    if( args[1].compare("--lb") == 0)
    {
        if( argc == 5)
        {
            if( args[2].compare( args[2].size()-5 , args[2].size() , ".maze" ) == 0 )
            {
                if( args[3].compare("--sv") == 0)
                {
                    if( args[4].compare( args[4].size()-4 , args[4].size() , ".svg" ) == 0)
                    {
                        // ./mazer --lb filename.maze --sv filename.svg
                        std::cout << "Loading maze from binary file and saving to svg file" << std::endl;
                        GrowingTree maze;
                        maze.loadMaze(args[2]);
                        maze.saveMazeSVG(args[4]);
                        return 1;
                    }
                }
            }
        }
    }
    else if( args[1].compare("--gp") == 0)
    {
        if( argc == 4 )
        {
            if( args[2].compare("--sb") == 0 )
            {
                if ( args[3].compare( args[3].size()-5 , args[3].size() , ".maze" ) == 0 )
                {
                    // ./mazer --g --sb filename.maze
                    std::cout << "generating a default prim maze and saving to binary" << std::endl;
                    Prim maze;
                    maze.generateMaze();
                    maze.saveMazeBinary( args[3] );
                    return 1;
                }
            }
            else if( args[2].compare("--sv") == 0 )
            {
                if(args[3].compare( args[3].size()-4 , args[3].size() , ".svg") == 0 )
                {
                    // ./mazer --g --sv filename.svg
                    std::cout << "generating a default prim maze and saving to svg" << std::endl;
                    Prim maze;
                    maze.generateMaze();
                    maze.saveMazeSVG( args[3] );
                    return 1;
                }
            }
        }
        else if( argc == 5 )
        {
            try
            {
                int seed = stoi(args[2]);
                if( args[3].compare("--sb") == 0 )
                {
                    if ( args[4].compare( args[4].size()-5 , args[4].size() , ".maze" ) == 0)
                    {
                        // ./mazer --g seed --sb filename.maze
                        std::cout << "generating prim with seed and saving to binary" << std::endl;
                        Prim maze(seed);
                        maze.generateMaze();
                        maze.saveMazeBinary( args[4] );
                        return 1;
                    }
                }
                else if ( args[3].compare("--sv") == 0 )
                {
                    if ( args[4].compare( args[4].size()-4 , args[4].size() , ".svg") == 0  )
                    {
                        // ./mazer --g seed --sv filename.svg
                        std::cout << "generating prim with seed and saving to svg" << std::endl;
                        Prim maze(seed);
                        maze.generateMaze();
                        maze.saveMazeSVG( args[4] );
                        return 1;
                    }
                }
            }
            catch(std::invalid_argument& e)
            {
                // if no conversion could be performed
                std::cout << "unable to convert seed to int..." << std::endl;
            }
            catch(std::out_of_range& e)
            {
                // if the converted value would fall out of the range of the result type
                // or if the underlying function (std::strtol or std::strtoull) sets errno
                // to ERANGE.
                std::cout << "unable to convert seed to int, string to long for int conversion" << std::endl;
            }
        }
        else if( argc == 6 )
        {
            if( args[2].compare("--sv") == 0 )
            {
                if( args[3].compare( args[3].size()-4 , args[3].size() , ".svg") == 0 )
                {
                    if( args[4].compare("--sb") == 0 )
                    {
                        if (  args[5].compare( args[5].size()-5 , args[5].size() , ".maze" ) == 0 )
                        {
                            // ./mazer --g --sv filename.svg --sb filename.maze
                            std::cout << "generating default prim maze and saving to binary and svg" << std::endl;
                            Prim maze;
                            maze.generateMaze();
                            maze.saveMazeSVG( args[3] );
                            maze.saveMazeBinary( args[5] );
                            return 1;
                        }
                    }
                }
            }
            else if(  args[2].compare("--sb") == 0 )
            {
                if( args[3].compare( args[3].size()-5 , args[3].size() , ".maze" ) == 0 )
                {
                    if( args[4].compare("--sv") == 0 )
                    {
                        if( args[5].compare( args[5].size()-4 , args[5].size() , ".svg") == 0 )
                        {
                            // ./mazer --g --sb filename.maze --sv filename.svg
                            std::cout << "generating default prim maze and saving to binary and svg" << std::endl;
                            Prim maze;
                            maze.generateMaze();
                            maze.saveMazeSVG( args[5] );
                            maze.saveMazeBinary( args[3] );
                            return 1;
                        }
                    }
                }
            }
        }
        else if( argc == 7 )
        {
            try
            {
                int seed = stoi(args[2]);
                int width = stoi(args[3]);
                int height = stoi(args[4]);

                if( args[3].compare("--sb") == 0 )
                {
                    if( args[4].compare( args[4].size()-5 , args[4].size() , ".maze" ) == 0 )
                    {
                        if( args[5].compare("--sv") == 0 )
                        {
                            if( args[6].compare( args[6].size()-4 , args[6].size() , ".svg") == 0 )
                            {
                                // ./mazer --g seed --sb filename.maze --sv filename.svg
                                std::cout << "generating prim with seed and saving to binary and svg " << std::endl;
                                Prim maze(seed);
                                maze.generateMaze();
                                maze.saveMazeBinary( args[4] );
                                maze.saveMazeSVG( args[6] );
                                return 1;
                            }
                        }
                    }
                }
                else if( args[3].compare("--sv") == 0 )
                {
                    if( args[4].compare( args[4].size()-4 , args[4].size() , ".svg") == 0 )
                    {
                        if( args[5].compare("--sb") == 0 )
                        {
                            if (  args[6].compare( args[6].size()-5 , args[6].size() , ".maze" ) == 0 )
                            {
                                // ./mazer --g seed --sv filename.svg --sb filename.maze
                                std::cout << "generating prim with seed and saving to binary and svg " << std::endl;
                                Prim maze(seed);
                                maze.generateMaze();
                                maze.saveMazeBinary( args[6] );
                                maze.saveMazeSVG( args[4] );
                                return 1;
                            }
                        }
                    }
                }
                else if ( (width>0) && (height>0) && (args[3].compare("--sv")!=0) && (args[3].compare("--sb") !=0) )
                {
                    if( args[5].compare("--sb") == 0 )
                    {
                        if (  args[6].compare( args[6].size()-5 , args[6].size() , ".maze" ) == 0 )
                        {
                            // ./mazer --g seed width height --sb filename.maze
                            std::cout << "generating prim with seed, width, height and saving to binary" << std::endl;
                            Prim maze(seed,width,height);
                            maze.generateMaze();
                            maze.saveMazeBinary( args[6] );
                            return 1;
                        }
                    }
                    else if( args[5].compare("--sv") == 0 )
                    {
                        if ( args[6].compare( args[6].size()-4 , args[6].size() , ".svg" ) == 0 )
                        {
                            // ./mazer --g seed width height --sv filename.svg
                            std::cout << "generating prim with seed, width, height and saving to svg" << std::endl;
                            Prim maze(seed,width,height);
                            maze.generateMaze();
                            maze.saveMazeSVG( args[6] );
                            return 1;
                        }
                    }
                }
            }
            catch(std::invalid_argument& e)
            {
                std::cout << "unable to convert seed, width or height to int..." << std::endl;
            }
            catch(std::out_of_range& e)
            {
                std::cout << "unable to convert seed, width or height to int, string to long for int conversion" << std::endl;
            }
        }
        else if( argc == 9 )
        {
            try
            {
                int seed = stoi(args[2]);
                int width = stoi(args[3]);
                int height = stoi(args[4]);

                if( (width>0) && (height>0) )
                {
                    if(  args[5].compare("--sb") == 0 )
                    {
                        if( args[6].compare( args[6].size()-5 , args[6].size() , ".maze" ) == 0 )
                        {
                            if( args[7].compare("--sv") == 0 )
                            {
                                if( args[8].compare( args[8].size()-4 , args[8].size() , ".svg") == 0 )
                                {
                                    // ./mazer --g seed width height --sb filename.maze --sv filename.svg
                                    std::cout << "generating prim with seed, width, height and saving to binary and svg" << std::endl;
                                    Prim maze(seed,width,height);
                                    maze.generateMaze();
                                    maze.saveMazeBinary( args[6] );
                                    maze.saveMazeSVG( args[8] );
                                    return 1;
                                }
                            }
                        }
                    }
                    else if( args[5].compare("--sv") == 0 )
                    {
                        if( args[6].compare( args[6].size()-4 , args[6].size() , ".svg") == 0 )
                        {
                            if( args[7].compare("--sb") == 0 )
                            {
                                if (  args[8].compare( args[8].size()-5 , args[8].size() , ".maze" ) == 0 )
                                {
                                    // ./mazer --g seed width height --sv filename.svg --sb filename.maze
                                    std::cout << "generating prim with seed, width, height and saving to binary and svg" << std::endl;
                                    Prim maze(seed,width,height);
                                    maze.generateMaze();
                                    maze.saveMazeBinary( args[8] );
                                    maze.saveMazeSVG( args[6] );
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }
            catch(std::invalid_argument& e)
            {
                std::cout << "unable to convert seed, width or height to int..." << std::endl;
            }
            catch(std::out_of_range& e)
            {
                std::cout << "unable to convert seed, width or height to int, string to long for int conversion" << std::endl;
            }
        }
    }
    else if( args[1].compare("--gr") == 0)
    {


        if( argc == 4 )
        {

            if( args[2].compare("--sb") == 0 )
            {
                if ( args[3].compare( args[3].size()-5 , args[3].size() , ".maze" ) == 0 )
                {
                    // ./mazer --g --sb filename.maze
                    std::cout << "generating a default RecursiveBackTracker maze and saving to binary" << std::endl;
                    RecursiveBackTracker maze;
                    maze.generateMaze();
                    maze.saveMazeBinary( args[3] );
                    return 1;
                }
            }
            else if( args[2].compare("--sv") == 0 )
            {
                // std::cout << "generating recursiveBackTracker 4" << std::endl;
                if(args[3].compare( args[3].size()-4 , args[3].size() , ".svg") == 0 )
                {
                    // ./mazer --g --sv filename.svg
                    std::cout << "generating a default RecursiveBackTracker maze and saving to svg" << std::endl;
                    RecursiveBackTracker maze;
                    maze.generateMaze();
                    maze.saveMazeSVG( args[3] );
                    return 1;
                }
            }
        }
        else if( argc == 5 )
        {
            try
            {
                int seed = stoi(args[2]);
                if( args[3].compare("--sb") == 0 )
                {
                    if ( args[4].compare( args[4].size()-5 , args[4].size() , ".maze" ) == 0)
                    {
                        // ./mazer --g seed --sb filename.maze
                        std::cout << "generating RecursiveBackTracker with seed and saving to binary" << std::endl;
                        RecursiveBackTracker maze(seed);
                        maze.generateMaze();
                        maze.saveMazeBinary( args[4] );
                        return 1;
                    }
                }
                else if ( args[3].compare("--sv") == 0 )
                {
                    if ( args[4].compare( args[4].size()-4 , args[4].size() , ".svg") == 0  )
                    {
                        // ./mazer --g seed --sv filename.svg
                        std::cout << "generating RecursiveBackTracker with seed and saving to svg" << std::endl;
                        RecursiveBackTracker maze(seed);
                        maze.generateMaze();
                        maze.saveMazeSVG( args[4] );
                        return 1;
                    }
                }
            }
            catch(std::invalid_argument& e)
            {
                // if no conversion could be performed
                std::cout << "unable to convert seed to int..." << std::endl;
            }
            catch(std::out_of_range& e)
            {
                // if the converted value would fall out of the range of the result type
                // or if the underlying function (std::strtol or std::strtoull) sets errno
                // to ERANGE.
                std::cout << "unable to convert seed to int, string to long for int conversion" << std::endl;
            }
        }
        else if( argc == 6 )
        {
            if( args[2].compare("--sv") == 0 )
            {
                if( args[3].compare( args[3].size()-4 , args[3].size() , ".svg") == 0 )
                {
                    if( args[4].compare("--sb") == 0 )
                    {
                        if (  args[5].compare( args[5].size()-5 , args[5].size() , ".maze" ) == 0 )
                        {
                            // ./mazer --g --sv filename.svg --sb filename.maze
                            std::cout << "generating RecursiveBackTracker default maze and saving to binary and svg" << std::endl;
                            RecursiveBackTracker maze;
                            maze.generateMaze();
                            maze.saveMazeSVG( args[3] );
                            maze.saveMazeBinary( args[5] );
                            return 1;
                        }
                    }
                }
            }
            else if(  args[2].compare("--sb") == 0 )
            {
                if( args[3].compare( args[3].size()-5 , args[3].size() , ".maze" ) == 0 )
                {
                    if( args[4].compare("--sv") == 0 )
                    {
                        if( args[5].compare( args[5].size()-4 , args[5].size() , ".svg") == 0 )
                        {
                            // ./mazer --g --sb filename.maze --sv filename.svg
                            std::cout << "generating RecursiveBackTracker default maze and saving to binary and svg" << std::endl;
                            RecursiveBackTracker maze;
                            maze.generateMaze();
                            maze.saveMazeSVG( args[5] );
                            maze.saveMazeBinary( args[3] );
                            return 1;
                        }
                    }
                }
            }
        }
        else if( argc == 7 )
        {
            try
            {
                int seed = stoi(args[2]);
                int width = stoi(args[3]);
                int height = stoi(args[4]);

                if( args[3].compare("--sb") == 0 )
                {
                    if( args[4].compare( args[4].size()-5 , args[4].size() , ".maze" ) == 0 )
                    {
                        if( args[5].compare("--sv") == 0 )
                        {
                            if( args[6].compare( args[6].size()-4 , args[6].size() , ".svg") == 0 )
                            {
                                // ./mazer --g seed --sb filename.maze --sv filename.svg
                                std::cout << "generating RecursiveBackTracker with seed and saving to binary and svg " << std::endl;
                                RecursiveBackTracker maze(seed);
                                maze.generateMaze();
                                maze.saveMazeBinary( args[4] );
                                maze.saveMazeSVG( args[6] );
                                return 1;
                            }
                        }
                    }
                }
                else if( args[3].compare("--sv") == 0 )
                {
                    if( args[4].compare( args[4].size()-4 , args[4].size() , ".svg") == 0 )
                    {
                        if( args[5].compare("--sb") == 0 )
                        {
                            if (  args[6].compare( args[6].size()-5 , args[6].size() , ".maze" ) == 0 )
                            {
                                // ./mazer --g seed --sv filename.svg --sb filename.maze
                                std::cout << "generating RecursiveBackTracker with seed and saving to binary and svg " << std::endl;
                                RecursiveBackTracker maze(seed);
                                maze.generateMaze();
                                maze.saveMazeBinary( args[6] );
                                maze.saveMazeSVG( args[4] );
                                return 1;
                            }
                        }
                    }
                }
                else if ( (width>0) && (height>0) && (args[3].compare("--sv")!=0) && (args[3].compare("--sb") !=0) )
                {
                    if( args[5].compare("--sb") == 0 )
                    {
                        if (  args[6].compare( args[6].size()-5 , args[6].size() , ".maze" ) == 0 )
                        {
                            // ./mazer --g seed width height --sb filename.maze
                            std::cout << "generating RecursiveBackTracker with seed, width, height and saving to binary" << std::endl;
                            RecursiveBackTracker maze(seed,width,height);
                            maze.generateMaze();
                            maze.saveMazeBinary( args[6] );
                            return 1;
                        }
                    }
                    else if( args[5].compare("--sv") == 0 )
                    {
                        if ( args[6].compare( args[6].size()-4 , args[6].size() , ".svg" ) == 0 )
                        {
                            // ./mazer --g seed width height --sv filename.svg
                            std::cout << "generating RecursiveBackTracker with seed, width, height and saving to svg" << std::endl;
                            RecursiveBackTracker maze(seed,width,height);
                            maze.generateMaze();
                            maze.saveMazeSVG( args[6] );
                            return 1;
                        }
                    }
                }
            }
            catch(std::invalid_argument& e)
            {
                std::cout << "unable to convert seed, width or height to int..." << std::endl;
            }
            catch(std::out_of_range& e)
            {
                std::cout << "unable to convert seed, width or height to int, string to long for int conversion" << std::endl;
            }
        }
        else if( argc == 9 )
        {
            try
            {
                int seed = stoi(args[2]);
                int width = stoi(args[3]);
                int height = stoi(args[4]);

                if( (width>0) && (height>0) )
                {
                    if(  args[5].compare("--sb") == 0 )
                    {
                        if( args[6].compare( args[6].size()-5 , args[6].size() , ".maze" ) == 0 )
                        {
                            if( args[7].compare("--sv") == 0 )
                            {
                                if( args[8].compare( args[8].size()-4 , args[8].size() , ".svg") == 0 )
                                {
                                    // ./mazer --g seed width height --sb filename.maze --sv filename.svg
                                    std::cout << "generating RecursiveBackTracker with seed, width, height and saving to binary and svg" << std::endl;
                                    RecursiveBackTracker maze(seed,width,height);
                                    maze.generateMaze();
                                    maze.saveMazeBinary( args[6] );
                                    maze.saveMazeSVG( args[8] );
                                    return 1;
                                }
                            }
                        }
                    }
                    else if( args[5].compare("--sv") == 0 )
                    {
                        if( args[6].compare( args[6].size()-4 , args[6].size() , ".svg") == 0 )
                        {
                            if( args[7].compare("--sb") == 0 )
                            {
                                if (  args[8].compare( args[8].size()-5 , args[8].size() , ".maze" ) == 0 )
                                {
                                    // ./mazer --g seed width height --sv filename.svg --sb filename.maze
                                    std::cout << "generating RecursiveBackTracker with seed, width, height and saving to binary and svg" << std::endl;
                                    RecursiveBackTracker maze(seed,width,height);
                                    maze.generateMaze();
                                    maze.saveMazeBinary( args[8] );
                                    maze.saveMazeSVG( args[6] );
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }
            catch(std::invalid_argument& e)
            {
                std::cout << "unable to convert seed, width or height to int..." << std::endl;
            }
            catch(std::out_of_range& e)
            {
                std::cout << "unable to convert seed, width or height to int, string to long for int conversion" << std::endl;
            }
        }
    }
    else if( args[1].compare("--pm") == 0 )
    {
        if( args[2].compare( args[2].size()-4 , args[2].size() , ".svg") == 0 )
        {
            if( args[3].compare("--gp") == 0 )
            {
                if( argc == 6 )
                {
                    if( args[4].compare("--sb") == 0 )
                    {
                        if ( args[5].compare( args[5].size()-5 , args[5].size() , ".maze" ) == 0 )
                        {
                            // ./mazer --g --sb filename.maze
                            std::cout << "generating a default prim maze and saving to binary and solving maze" << std::endl;
                            Prim maze;
                            maze.generateMaze();
                            maze.saveMazeBinary( args[5] );
                            maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                            return 1;
                        }
                    }
                    else if( args[4].compare("--sv") == 0 )
                    {
                        if(args[5].compare( args[5].size()-4 , args[5].size() , ".svg") == 0 )
                        {
                            // ./mazer --g --sv filename.svg
                            std::cout << "generating a default prim maze and saving to svg and solving maze" << std::endl;
                            Prim maze;
                            maze.generateMaze();
                            maze.saveMazeSVG( args[5] );
                            maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                            return 1;
                        }
                    }
                }
                else if( argc == 7 )
                {
                    try
                    {
                        int seed = stoi(args[2]);
                        if( args[5].compare("--sb") == 0 )
                        {
                            if ( args[6].compare( args[6].size()-5 , args[6].size() , ".maze" ) == 0)
                            {
                                // ./mazer --g seed --sb filename.maze
                                std::cout << "generating prim with seed and saving to binary and solving maze" << std::endl;
                                Prim maze(seed);
                                maze.generateMaze();
                                maze.saveMazeBinary( args[6] );
                                maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );

                                return 1;
                            }
                        }
                        else if ( args[5].compare("--sv") == 0 )
                        {
                            if ( args[6].compare( args[6].size()-4 , args[6].size() , ".svg") == 0  )
                            {
                                // ./mazer --g seed --sv filename.svg
                                std::cout << "generating prim with seed and saving to svg and solving maze" << std::endl;
                                Prim maze(seed);
                                maze.generateMaze();
                                maze.saveMazeSVG( args[6] );
                                maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                                return 1;
                            }
                        }
                    }
                    catch(std::invalid_argument& e)
                    {
                        // if no conversion could be performed
                        std::cout << "unable to convert seed to int..." << std::endl;
                    }
                    catch(std::out_of_range& e)
                    {
                        // if the converted value would fall out of the range of the result type
                        // or if the underlying function (std::strtol or std::strtoull) sets errno
                        // to ERANGE.
                        std::cout << "unable to convert seed to int, string to long for int conversion" << std::endl;
                    }
                }
                else if( argc == 8 )
                {
                    if( args[4].compare("--sv") == 0 )
                    {
                        if( args[5].compare( args[5].size()-4 , args[5].size() , ".svg") == 0 )
                        {
                            if( args[6].compare("--sb") == 0 )
                            {
                                if (  args[7].compare( args[7].size()-5 , args[7].size() , ".maze" ) == 0 )
                                {
                                    // ./mazer --g --sv filename.svg --sb filename.maze
                                    std::cout << "generating default prim maze and saving to binary and svg and solving maze" << std::endl;
                                    Prim maze;
                                    maze.generateMaze();
                                    maze.saveMazeSVG( args[5] );
                                    maze.saveMazeBinary( args[7] );
                                    maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                                    return 1;
                                }
                            }
                        }
                    }
                    else if(  args[4].compare("--sb") == 0 )
                    {
                        if( args[5].compare( args[5].size()-5 , args[5].size() , ".maze" ) == 0 )
                        {
                            if( args[6].compare("--sv") == 0 )
                            {
                                if( args[7].compare( args[7].size()-4 , args[7].size() , ".svg") == 0 )
                                {
                                    // ./mazer --g --sb filename.maze --sv filename.svg
                                    std::cout << "generating default prim maze and saving to binary and svg and solving maze" << std::endl;
                                    Prim maze;
                                    maze.generateMaze();
                                    maze.saveMazeSVG( args[7] );
                                    maze.saveMazeBinary( args[5] );
                                    maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                                    return 1;
                                }
                            }
                        }
                    }
                }
                else if( argc == 9 )
                {
                    try
                    {
                        int seed = stoi(args[4]);
                        int width = stoi(args[5]);
                        int height = stoi(args[6]);

                        if( args[5].compare("--sb") == 0 )
                        {
                            if( args[6].compare( args[6].size()-5 , args[6].size() , ".maze" ) == 0 )
                            {
                                if( args[7].compare("--sv") == 0 )
                                {
                                    if( args[8].compare( args[8].size()-4 , args[8].size() , ".svg") == 0 )
                                    {
                                        // ./mazer --g seed --sb filename.maze --sv filename.svg
                                        std::cout << "generating prim with seed and saving to binary and svg and solving maze" << std::endl;
                                        Prim maze(seed);
                                        maze.generateMaze();
                                        maze.saveMazeBinary( args[6] );
                                        maze.saveMazeSVG( args[8] );
                                        maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                                        return 1;
                                    }
                                }
                            }
                        }
                        else if( args[5].compare("--sv") == 0 )
                        {
                            if( args[6].compare( args[6].size()-4 , args[6].size() , ".svg") == 0 )
                            {
                                if( args[7].compare("--sb") == 0 )
                                {
                                    if (  args[8].compare( args[8].size()-5 , args[8].size() , ".maze" ) == 0 )
                                    {
                                        // ./mazer --g seed --sv filename.svg --sb filename.maze
                                        std::cout << "generating prim with seed and saving to binary and svg and solving maze " << std::endl;
                                        Prim maze(seed);
                                        maze.generateMaze();
                                        maze.saveMazeBinary( args[8] );
                                        maze.saveMazeSVG( args[6] );
                                        maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                                        return 1;
                                    }
                                }
                            }
                        }
                        else if ( (width>0) && (height>0) && (args[5].compare("--sv")!=0) && (args[5].compare("--sb") !=0) )
                        {
                            if( args[7].compare("--sb") == 0 )
                            {
                                if (  args[8].compare( args[8].size()-5 , args[8].size() , ".maze" ) == 0 )
                                {
                                    // ./mazer --g seed width height --sb filename.maze
                                    std::cout << "generating prim with seed, width, height and saving to binary and solving maze" << std::endl;
                                    Prim maze(seed,width,height);
                                    maze.generateMaze();
                                    maze.saveMazeBinary( args[8] );
                                    maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                                    return 1;
                                }
                            }
                            else if( args[7].compare("--sv") == 0 )
                            {
                                if ( args[8].compare( args[8].size()-4 , args[8].size() , ".svg" ) == 0 )
                                {
                                    // ./mazer --g seed width height --sv filename.svg
                                    std::cout << "generating prim with seed, width, height and saving to svg and solving maze" << std::endl;
                                    Prim maze(seed,width,height);
                                    maze.generateMaze();
                                    maze.saveMazeSVG( args[8] );
                                    maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                                    return 1;
                                }
                            }
                        }
                    }
                    catch(std::invalid_argument& e)
                    {
                        std::cout << "unable to convert seed, width or height to int..." << std::endl;
                    }
                    catch(std::out_of_range& e)
                    {
                        std::cout << "unable to convert seed, width or height to int, string to long for int conversion" << std::endl;
                    }
                }
                else if( argc == 11 )
                {
                    try
                    {
                        int seed = stoi(args[4]);
                        int width = stoi(args[5]);
                        int height = stoi(args[6]);

                        if( (width>0) && (height>0) )
                        {
                            if(  args[7].compare("--sb") == 0 )
                            {
                                if( args[8].compare( args[8].size()-5 , args[8].size() , ".maze" ) == 0 )
                                {
                                    if( args[9].compare("--sv") == 0 )
                                    {
                                        if( args[10].compare( args[10].size()-4 , args[10].size() , ".svg") == 0 )
                                        {
                                            // ./mazer --g seed width height --sb filename.maze --sv filename.svg
                                            std::cout << "generating prim with seed, width, height and saving to binary and svg and solving maze" << std::endl;
                                            Prim maze(seed,width,height);
                                            maze.generateMaze();
                                            maze.saveMazeBinary( args[8] );
                                            maze.saveMazeSVG( args[10] );
                                            maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                                            return 1;
                                        }
                                    }
                                }
                            }
                            else if( args[7].compare("--sv") == 0 )
                            {
                                if( args[8].compare( args[8].size()-4 , args[8].size() , ".svg") == 0 )
                                {
                                    if( args[9].compare("--sb") == 0 )
                                    {
                                        if (  args[10].compare( args[10].size()-5 , args[10].size() , ".maze" ) == 0 )
                                        {
                                            // ./mazer --g seed width height --sv filename.svg --sb filename.maze
                                            std::cout << "generating prim with seed, width, height and saving to binary and svg and solving maze" << std::endl;
                                            Prim maze(seed,width,height);
                                            maze.generateMaze();
                                            maze.saveMazeBinary( args[10] );
                                            maze.saveMazeSVG( args[8] );
                                            maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                                            return 1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    catch(std::invalid_argument& e)
                    {
                        std::cout << "unable to convert seed, width or height to int..." << std::endl;
                    }
                    catch(std::out_of_range& e)
                    {
                        std::cout << "unable to convert seed, width or height to int, string to long for int conversion" << std::endl;
                    }
                }
            }
            else if( args[3].compare("--gr") == 0)
            {
                if( argc == 6 )
                {
                    if( args[4].compare("--sb") == 0 )
                    {
                        if ( args[5].compare( args[5].size()-5 , args[5].size() , ".maze" ) == 0 )
                        {
                            // ./mazer --g --sb filename.maze
                            std::cout << "generating a default RecursiveBackTracker maze and saving to binary and solving maze" << std::endl;
                            RecursiveBackTracker maze;
                            maze.generateMaze();
                            maze.saveMazeBinary( args[5] );
                            maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                            return 1;
                        }
                    }
                    else if( args[4].compare("--sv") == 0 )
                    {
                        if(args[5].compare( args[5].size()-4 , args[5].size() , ".svg") == 0 )
                        {
                            // ./mazer --g --sv filename.svg
                            std::cout << "generating a default RecursiveBackTracker maze and saving to svg and solving maze" << std::endl;
                            RecursiveBackTracker maze;
                            maze.generateMaze();
                            maze.saveMazeSVG( args[5] );
                            maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                            return 1;
                        }
                    }
                }
                else if( argc == 7 )
                {
                    try
                    {
                        int seed = stoi(args[4]);
                        if( args[5].compare("--sb") == 0 )
                        {
                            if ( args[6].compare( args[6].size()-5 , args[6].size() , ".maze" ) == 0)
                            {
                                // ./mazer --g seed --sb filename.maze
                                std::cout << "generating RecursiveBackTracker with seed and saving to binary and solving maze" << std::endl;
                                RecursiveBackTracker maze(seed);
                                maze.generateMaze();
                                maze.saveMazeBinary( args[6] );
                                maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                                return 1;
                            }
                        }
                        else if ( args[5].compare("--sv") == 0 )
                        {
                            if ( args[6].compare( args[6].size()-4 , args[6].size() , ".svg") == 0  )
                            {
                                // ./mazer --g seed --sv filename.svg
                                std::cout << "generating RecursiveBackTracker with seed and saving to svg and solving maze" << std::endl;
                                RecursiveBackTracker maze(seed);
                                maze.generateMaze();
                                maze.saveMazeSVG( args[6] );
                                maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                                return 1;
                            }
                        }
                    }
                    catch(std::invalid_argument& e)
                    {
                        // if no conversion could be performed
                        std::cout << "unable to convert seed to int..." << std::endl;
                    }
                    catch(std::out_of_range& e)
                    {
                        // if the converted value would fall out of the range of the result type
                        // or if the underlying function (std::strtol or std::strtoull) sets errno
                        // to ERANGE.
                        std::cout << "unable to convert seed to int, string to long for int conversion and solving maze" << std::endl;
                    }
                }
                else if( argc == 8 )
                {
                    if( args[4].compare("--sv") == 0 )
                    {
                        if( args[5].compare( args[5].size()-4 , args[5].size() , ".svg") == 0 )
                        {
                            if( args[6].compare("--sb") == 0 )
                            {
                                if (  args[7].compare( args[7].size()-5 , args[7].size() , ".maze" ) == 0 )
                                {
                                    // ./mazer --g --sv filename.svg --sb filename.maze
                                    std::cout << "generating RecursiveBackTracker default maze and saving to binary and svg and solving maze" << std::endl;
                                    RecursiveBackTracker maze;
                                    maze.generateMaze();
                                    maze.saveMazeSVG( args[5] );
                                    maze.saveMazeBinary( args[7] );
                                    maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                                    return 1;
                                }
                            }
                        }
                    }
                    else if(  args[4].compare("--sb") == 0 )
                    {
                        if( args[5].compare( args[5].size()-5 , args[5].size() , ".maze" ) == 0 )
                        {
                            if( args[6].compare("--sv") == 0 )
                            {
                                if( args[7].compare( args[7].size()-4 , args[7].size() , ".svg") == 0 )
                                {
                                    // ./mazer --g --sb filename.maze --sv filename.svg
                                    std::cout << "generating RecursiveBackTracker default maze and saving to binary and svg and solving maze" << std::endl;
                                    RecursiveBackTracker maze;
                                    maze.generateMaze();
                                    maze.saveMazeSVG( args[7] );
                                    maze.saveMazeBinary( args[5] );
                                    maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                                    return 1;
                                }
                            }
                        }
                    }
                }
                else if( argc == 9 )
                {
                    try
                    {
                        int seed = stoi(args[4]);
                        int width = stoi(args[5]);
                        int height = stoi(args[6]);

                        if( args[5].compare("--sb") == 0 )
                        {
                            if( args[6].compare( args[6].size()-5 , args[6].size() , ".maze" ) == 0 )
                            {
                                if( args[7].compare("--sv") == 0 )
                                {
                                    if( args[8].compare( args[8].size()-4 , args[8].size() , ".svg") == 0 )
                                    {
                                        // ./mazer --g seed --sb filename.maze --sv filename.svg
                                        std::cout << "generating RecursiveBackTracker with seed and saving to binary and svg and solving maze " << std::endl;
                                        RecursiveBackTracker maze(seed);
                                        maze.generateMaze();
                                        maze.saveMazeBinary( args[6] );
                                        maze.saveMazeSVG( args[8] );
                                        maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                                        return 1;
                                    }
                                }
                            }
                        }
                        else if( args[5].compare("--sv") == 0 )
                        {
                            if( args[6].compare( args[6].size()-4 , args[6].size() , ".svg") == 0 )
                            {
                                if( args[7].compare("--sb") == 0 )
                                {
                                    if (  args[8].compare( args[8].size()-5 , args[8].size() , ".maze" ) == 0 )
                                    {
                                        // ./mazer --g seed --sv filename.svg --sb filename.maze
                                        std::cout << "generating RecursiveBackTracker with seed and saving to binary and svg  and solving maze" << std::endl;
                                        RecursiveBackTracker maze(seed);
                                        maze.generateMaze();
                                        maze.saveMazeBinary( args[8] );
                                        maze.saveMazeSVG( args[6] );
                                        maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                                        return 1;
                                    }
                                }
                            }
                        }
                        else if ( (width>0) && (height>0) && (args[5].compare("--sv")!=0) && (args[5].compare("--sb") !=0) )
                        {
                            if( args[7].compare("--sb") == 0 )
                            {
                                if (  args[8].compare( args[8].size()-5 , args[8].size() , ".maze" ) == 0 )
                                {
                                    // ./mazer --g seed width height --sb filename.maze
                                    std::cout << "generating RecursiveBackTracker with seed, width, height and saving to binary and solving maze" << std::endl;
                                    RecursiveBackTracker maze(seed,width,height);
                                    maze.generateMaze();
                                    maze.saveMazeBinary( args[8] );
                                    maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                                    return 1;
                                }
                            }
                            else if( args[7].compare("--sv") == 0 )
                            {
                                if ( args[8].compare( args[8].size()-4 , args[8].size() , ".svg" ) == 0 )
                                {
                                    // ./mazer --g seed width height --sv filename.svg
                                    std::cout << "generating RecursiveBackTracker with seed, width, height and saving to svg and solving maze" << std::endl;
                                    RecursiveBackTracker maze(seed,width,height);
                                    maze.generateMaze();
                                    maze.saveMazeSVG( args[8] );
                                    maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                                    return 1;
                                }
                            }
                        }
                    }
                    catch(std::invalid_argument& e)
                    {
                        std::cout << "unable to convert seed, width or height to int..." << std::endl;
                    }
                    catch(std::out_of_range& e)
                    {
                        std::cout << "unable to convert seed, width or height to int, string to long for int conversion" << std::endl;
                    }
                }
                else if( argc == 11 )
                {
                    try
                    {
                        int seed = stoi(args[4]);
                        int width = stoi(args[5]);
                        int height = stoi(args[6]);

                        if( (width>0) && (height>0) )
                        {
                            if(  args[7].compare("--sb") == 0 )
                            {
                                if( args[8].compare( args[8].size()-5 , args[8].size() , ".maze" ) == 0 )
                                {
                                    if( args[9].compare("--sv") == 0 )
                                    {
                                        if( args[10].compare( args[10].size()-4 , args[10].size() , ".svg") == 0 )
                                        {
                                            // ./mazer --g seed width height --sb filename.maze --sv filename.svg
                                            std::cout << "generating RecursiveBackTracker with seed, width, height and saving to binary and svg and solving maze" << std::endl;
                                            RecursiveBackTracker maze(seed,width,height);
                                            maze.generateMaze();
                                            maze.saveMazeBinary( args[8] );
                                            maze.saveMazeSVG( args[10] );
                                            maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                                            return 1;
                                        }
                                    }
                                }
                            }
                            else if( args[7].compare("--sv") == 0 )
                            {
                                if( args[8].compare( args[8].size()-4 , args[8].size() , ".svg") == 0 )
                                {
                                    if( args[9].compare("--sb") == 0 )
                                    {
                                        if (  args[10].compare( args[10].size()-5 , args[10].size() , ".maze" ) == 0 )
                                        {
                                            // ./mazer --g seed width height --sv filename.svg --sb filename.maze
                                            std::cout << "generating RecursiveBackTracker with seed, width, height and saving to binary and svg and solving maze" << std::endl;
                                            RecursiveBackTracker maze(seed,width,height);
                                            maze.generateMaze();
                                            maze.saveMazeBinary( args[10] );
                                            maze.saveMazeSVG( args[8] );
                                            maze.findPath( maze.getGridWidth(),maze.getGridHeight(), args[2] );
                                            return 1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    catch(std::invalid_argument& e)
                    {
                        std::cout << "unable to convert seed, width or height to int..." << std::endl;
                    }
                    catch(std::out_of_range& e)
                    {
                        std::cout << "unable to convert seed, width or height to int, string to long for int conversion" << std::endl;
                    }
                }
            }

            return 1;
        }
    }

    // if here args were wrong
    std::cout << "invaid command argument, exiting system..." << std::endl;
    return 0;
}
