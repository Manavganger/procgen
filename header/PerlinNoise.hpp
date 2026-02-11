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
        float noiseScale;

        std::array<Vector, 4> findOffsets(float x, float y);
        Vector generateUnitVector(void);
        float dot(Vector& v1, Vector& v2);
        float clamp(float x, float lowerlimit = 0.0f, float upperlimit = 1.0f);
        float smoothstep(float edge0, float edge1, float x);
        float addOctaves(float x, float y);

    public:
        PerlinNoise(GridPtr tiles, Size gridSize, int octaves, float noiseScale);
        void generateNoise(void);
};

#endif