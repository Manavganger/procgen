#ifndef PERLIN_NOISE_HPP
#define PERLIN_NOISE_HPP

#include "Common.hpp"

class PerlinNoise
{
    private:
        GridPtr tiles;
        Size gridSize;
        Size noiseGridSize;
        PerlinGrid noiseGrid;
        int octaves;

        Vector generateUnitVector(void);

    public:
        PerlinNoise(GridPtr tiles, Size noiseGridSize, Size gridSize, int octaves);
        void generateNoise(void);
};

#endif