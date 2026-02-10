#include "../header/PerlinNoise.hpp"

PerlinNoise::PerlinNoise(GridPtr tiles, Size noiseGridSize, Size gridSize, int octaves) 
    : tiles(tiles), noiseGridSize(noiseGridSize), gridSize(gridSize), octaves(octaves)
{
    noiseGrid.resize(noiseGridSize.rows);
    for (int r = 0; r < noiseGridSize.rows; ++r)
    {
        noiseGrid[r].resize(noiseGridSize.cols);
        for (int c = 0; c < noiseGridSize.cols; ++c)
        {
            noiseGrid[r][c] = generateUnitVector();
        }
    }
}

Vector PerlinNoise::generateUnitVector(void)
{
    // generate random angle. See https://stackoverflow.com/questions/288739/generate-random-numbers-uniformly-over-an-entire-range#20136256

    static std::mt19937 rng(std::random_device{}());
    static std::uniform_real_distribution<float> dist(0.0f, 2.0f * PI);
    float theta = dist(rng);
    
    Vector v;
    v.x = cos(theta);
    v.y = sin(theta);
    return v;
}

// idea is to create noise values, [-1, 1], and then use a threshold, T, to determine what's 'land'
// and what's 'water'. Anything lower than T is water; anything higher, land. Note that 2 maps to, 
// water, 3 maps to land. 
void PerlinNoise::generateNoise(void)
{
    
}

