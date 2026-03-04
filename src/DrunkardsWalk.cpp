#include "../header/DrunkardsWalk.hpp"

DrunkardsWalk::DrunkardsWalk(GridPtr tiles, Size maxSize, int walkLen, float minCover): 
    tiles(tiles), 
    maxSize(maxSize),
    walkLen(walkLen), 
    minCover(minCover),
    visited(maxSize.rows * maxSize.cols, false)
{}

bool DrunkardsWalk::checkVisited(int r, int c)
{
    return visited[maxSize.rows * r + c];
}

void DrunkardsWalk::addVisited(int r, int c)
{
    visited[maxSize.rows * r + c] = true;
    visitedList.emplace_back({r, c});
}

bool DrunkardsWalk::enoughGridCover(void)
{
    return (( visitedCount / (maxSize.rows * maxSize.cols) ) >= minCover);
}

Position DrunkardsWalk::getRandomTile(void)
{
    int idx = rand() % visitedList.size();
    return visitedList[idx];
}

void DrunkardsWalk::updateGrid(void)
{
    // get first random tile

    while !(enoughGridCover())
    {

    }
}