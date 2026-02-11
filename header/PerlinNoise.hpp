#ifndef PERLIN_NOISE_HPP
#define PERLIN_NOISE_HPP

#include "Common.hpp"
#include <random>
#include <cmath>

class PerlinNoise
{
    private:
        GridPtr tiles;
        Size gridSize;
        PerlinGrid noiseGrid;
        int octaves;

        std::array<int, 8> findCorners(float x, float y);
        float dot(Vector& v1, Vector& v2);
        Vector generateUnitVector(void);

    public:
        PerlinNoise(GridPtr tiles, Size gridSize, int octaves);
        void generateNoise(void);
};

#endif