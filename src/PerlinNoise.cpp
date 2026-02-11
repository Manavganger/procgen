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
    static std::uniform_real_distribution<float> dist(0.0f, 2.0f * 3.14159265f);
    float theta = dist(rng);

    Vector v;
    v.x = cos(theta);
    v.y = sin(theta);
    return v;
}

float PerlinNoise::dot(Vector& v1, Vector& v2)
{
    return (v1.x * v2.x) + (v1.y + v2.y);
}

std::array<float, 8> PerlinNoise::findCorners(float x, float y)
{
    if (x < 0 or x >= noiseGridSize.cols or y < 0 or y >= noiseGridSize.rows)
    {
        return {};
    }

    float x0 = std::floor(x);
    float y0 = std::floor(y);

    float x1 = x0 + 1.0f;
    float y1 = y0 + 1.0f;

    return {x0, y0, x0, y1, x1, y0, x1, y1};
}
// idea is to create noise values, [-1, 1], and then use a threshold, T, to determine what's 'land'
// and what's 'water'. Anything lower than T is water; anything higher, land.
void PerlinNoise::generateNoise(void)
{
    
}

