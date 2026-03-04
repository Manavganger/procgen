#include "../header/DrunkardsWalk.hpp"

DrunkardsWalk::DrunkardsWalk(GridPtr tiles, Size maxSize, int walkLen, float minCover): 
    tiles(tiles), 
    maxSize(maxSize),
    walkLen(walkLen), 
    minCover(minCover),
    visited(maxSize.rows * maxSize.cols, false)
{}

bool DrunkardsWalk::checkVisited(Position p)
{
    return visited[maxSize.rows * p.row + p.col];
}

void DrunkardsWalk::addVisited(Position p)
{
    visited[maxSize.rows * p.row + p.col] = true;
    visitedList.emplace_back({p.row, p.col});
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

void DrunkardsWalk::drunkWalkIteration(Position p)
{ 
    addVisited(p);  

    // seed random numbers. 
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 3);
    
    Position curr = p;
    for (int i = 0; i < walkLen; ++i)
    {
        int val = dist(rng);

        // choose random direction to walk in
        switch (val)
        {
        case 0:
            curr.row++;
            break;
        case 1:
            curr.row--;
            break;
        case 2:
            curr.col++;
            break;
        default:
            curr.col--;
            break;
        }

        // immediately stop if out of bounds
        if (curr.row >= maxSize.rows or curr.col >= maxSize.cols or curr.row <= 0 or curr.col <= 0)
        {
            return 
        }

        addVisited(curr);
    }
}

// Drunkard's walk algo is as follows: Pick a random tile to start at. Randomly 'walk' starting from that tile until you either: 
//   1. go out of bounds, 
//   2. reach the prespecifed length of the walk
// Mark each tile in the walk as visited. Then, do another random walk starting from an already visited tile. Repeat until you
// have visited a certain percentage of the grid. 
void DrunkardsWalk::updateGrid(void)
{
    // this base case should never happen but just in case
    if (minCover == 0.0f)
    {
        return;
    }

    int r = rand() % maxSize.rows;
    int c = rand() % maxSize.cols;
    drunkWalkIteration({r, c});

    while !(enoughGridCover())
    {
        Position p = getRandomTile();
        drunkWalkIteration(p)
    }
}