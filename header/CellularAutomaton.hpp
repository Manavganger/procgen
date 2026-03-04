#ifndef CELLULAR_AUTOMATON_HPP
#define CELLULAR_AUTOMATON_HPP
#include "Common.hpp"

class CellularAutomaton
{
    private:
        const Size maxSize;
        const int iterations;
        GridPtr currState;
        GridPtr prevState;

        int countAliveNeighbors(Position p);
        TileType neighborsToState(int aliveNeighborCount);

    public:
        CellularAutomaton(GridPtr tiles, Size maxSize, int iterations);
        void updateGrid(void);
};
#endif