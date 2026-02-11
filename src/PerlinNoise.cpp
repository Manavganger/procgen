#include "../header/PerlinNoise.hpp"

PerlinNoise::PerlinNoise(GridPtr tiles, Size gridSize, int octaves) 
    : tiles(tiles), gridSize(gridSize), octaves(octaves)
{
    noiseGrid.resize(gridSize.rows);
    for (int r = 0; r < gridSize.rows; ++r)
    {
        noiseGrid[r].resize(gridSize.cols);
        for (int c = 0; c < gridSize.cols; ++c)
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

std::array<Vector, 4> PerlinNoise::findOffsets(float x, float y)
{
    if (x < 0 or x >= gridSize.cols - 1 or y < 0 or y >= gridSize.rows - 1)
    {
        return {};
    }

    float x0 = std::floor(x);
    float y0 = std::floor(y);

    float x1 = x0 + 1.0f;
    float y1 = y0 + 1.0f;

    return {{
        {x - x0, y - y0},
        {x - x1, y - y0},
        {x - x0, y - y1},
        {x - x1, y - y1}
    }};
}

float PerlinNoise::smoothstep(float edge0, float edge1, float x) 
{
    // Scale, and clamp x to 0..1 range
    x = clamp((x - edge0) / (edge1 - edge0));

    return x * x * (3.0f - 2.0f * x);
}

float PerlinNoise::clamp(float x, float lowerlimit, float upperlimit) 
{
    if (x < lowerlimit) return lowerlimit;
    if (x > upperlimit) return upperlimit;
    return x;
}

// idea is to create noise values, [-1, 1], and then use a threshold, T, to determine what's 'land'
// and what's 'water'. Anything lower than T is water; anything higher, land.
void PerlinNoise::generateNoise(void)
{
    
}

