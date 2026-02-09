#ifndef PERLIN_NOISE_HPP
#define PERLIN_NOISE_HPP

#include "Size.hpp"
#include "Vector.hpp"

class PerlinNoise
{
    private:
        int** tiles;
        Size gridSize;

    public:
        PerlinNoise(int** tiles, Size gridSize);
        generateNoise();
};

#endif