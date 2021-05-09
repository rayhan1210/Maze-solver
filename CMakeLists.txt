CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# Set options for this project.
SET (PROJECT_NAME "Mazer" CXX)
SET (CMAKE_CXX_FLAGS "-Wall -pedantic -std=c++14 -g")
SET (PROJECT_SOURCE_DEFINITION_DIRECTORY ${PROJECT_SOURCE_DIR}src/)
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}bin/)

set(SOURCE_FILES  src/main.cpp src/growingTree.cpp src/recursiveBackTracker.cpp src/prim.cpp src/cell.cpp src/edge.cpp )

project (${PROJECT_NAME})

include_directories(include)
include_directories(src)

ADD_EXECUTABLE(mazer ${SOURCE_FILES})
