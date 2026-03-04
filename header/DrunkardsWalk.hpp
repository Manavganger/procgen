#ifndef DRUNKARDS_WALK
#define DRUNKARDS_WALK
#include "Common.hpp"

class DrunkardsWalk
{
    private:
        const Size maxSize;
        const int walkLen;              // how many "steps" the drunkard walks
        const float minCover;           // what percent of the map needs to be covered before stopping 
        GridPtr tiles;

    public:
        DrunkardsWalk(GridPtr tiles, Size maxSize, int walkLen, float minCover);
        void updateGrid(void);
}

#endif