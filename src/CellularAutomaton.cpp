#include "../header/CellularAutomaton.hpp"

CellularAutomaton::CellularAutomaton(GridPtr tiles, Size maxSize, int iterations) : tiles(tiles), maxSize(maxSize), iterations(iterations)
{
    //See https://stackoverflow.com/questions/288739/generate-random-numbers-uniformly-over-an-entire-range#20136256
    static std::mt19937 rng(std::random_device{}());
    std::bernoulli_distribution dist(0.5); 

    for (int r = 0; r < maxSize.rows; ++r)
    {
        for (int c = 0; c < maxSize.cols; ++c)
        {
            (*tiles)[r][c] = dist(rng) ? TileType::Wall : TileType::Open;
        }
    }
}

void CellularAutomaton::updateGrid(void)
{

}