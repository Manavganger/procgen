#ifndef PERLIN_NOISE_HPP
#define PERLIN_NOISE_HPP

#include "Common.hpp"

class PerlinNoise
{
    private:
        GridPtr tiles;
        Size gridSize;

    public:
        PerlinNoise(GridPtr tiles, Size gridSize);
        void generateNoise(void);
};

#endif