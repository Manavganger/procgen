#include "../header/PerlinNoise.hpp"

PerlinNoise::PerlinNoise(GridPtr tiles, Size gridSize): tiles(tiles), gridSize(gridSize)
{
    // leave empty 
}

// idea is to create noise values, [-1, 1], and then use a threshold, T, to determine what's 'land'
// and what's 'water'. Anything lower than T is water; anything higher, land. Note that 2 maps to, 
// water, 3 maps to land. 
void PerlinNoise::generateNoise(void)
{
    
}