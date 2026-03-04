#ifndef DRUNKARDS_WALK
#define DRUNKARDS_WALK
#include "Common.hpp"

class DrunkardsWalk
{
    private:
        const Size maxSize;
        const int walkLen;              // how many "steps" the drunkard walks before stopping 
        const float minCover;           // what percent of the map needs to be covered before stopping 
        int visitedCount = 0;

        GridPtr tiles;
        BitArray visited;
        std::vector<Position> visitedList;

        const bool enoughGridCover(void);
        const bool checkVisited(int r, int c);
        const int[] getRandomTile(void);
        void addVisited(int r, int c);

    public:
        DrunkardsWalk(GridPtr tiles, Size maxSize, int walkLen, float minCover);
        void updateGrid(void);
}

#endif