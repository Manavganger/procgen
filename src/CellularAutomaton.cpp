#include "../header/CellularAutomaton.hpp"

// Assign each tile to either Wall or Open. 50/50 coin flip. 
CellularAutomaton::CellularAutomaton(GridPtr tiles, Size maxSize, int iterations) : prevState(tiles), maxSize(maxSize), iterations(iterations)
{
    //See https://stackoverflow.com/questions/288739/generate-random-numbers-uniformly-over-an-entire-range#20136256
    static std::mt19937 rng(std::random_device{}());
    std::bernoulli_distribution dist(0.5); 

    for (int r = 0; r < maxSize.rows; ++r)
    {
        for (int c = 0; c < maxSize.cols; ++c)
        {
            (*prevState)[r][c] = dist(rng) ? TileType::Wall : TileType::Open;
        }
    }
    currState = std::make_shared<Grid>(*prevState);
}

int CellularAutomaton::countAliveNeighbors(int r, int c)
{
    int count = 0;

    for (int dr = -1; dr <= 1; ++dr)
    {
        for (int dc = -1; dc <= 1; ++dc)
        {
            // Skip the cell itself
            if (dr == 0 and dc == 0)
                continue;

            int nr = r + dr;
            int nc = c + dc;

            if (nr >= 0 and nr < maxSize.rows and nc >= 0 and nc < maxSize.cols)
            {
                if ((*prevState)[nr][nc] == TileType::Wall)
                {
                    ++count;
                }
            }
        }
    }

    return count;
}


TileType CellularAutomaton::neighborsToState(int aliveNeighborCount)
{
    return (aliveNeighborCount <= 4) ? TileType::Wall : TileType::Open;
}

// plays "game of life" with given grid. For a given tile, if enough tiles around it are open, it will also become open.
// If enough tiles are walls, then it becomes a wall. All tiles updated 'simultaneously', so previous state is remembered.
void CellularAutomaton::updateGrid(void)
{
    for (int i = 0; i < iterations; ++i)
    {
        for (int r = 0; r < maxSize.rows; ++r)
        {
            for (int c = 0; c < maxSize.cols; ++c)
            {
                int count = countAliveNeighbors(r, c);
                (*currState)[r][c] = neighborsToState(count);
            }
        }
        std::swap(currState, prevState);
    }
}