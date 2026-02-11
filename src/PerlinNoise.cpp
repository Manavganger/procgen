#include "../header/PerlinNoise.hpp"

PerlinNoise::PerlinNoise(GridPtr tiles, Size gridSize, int octaves, float noiseScale) 
    : tiles(tiles), gridSize(gridSize), octaves(octaves), noiseScale(noiseScale)
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
    return (v1.x * v2.x) + (v1.y * v2.y);
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

float PerlinNoise::addOctaves(float x, float y)
{
    float total = 0.0f;
    float frequency = 1.0f;
    float amplitude = 1.0f;
    float maxAmplitude = 0.0f;

    for (int o = 0; o < octaves; ++o)
    {
        // sample noise at current frequency
        float sampleX = x * frequency * noiseScale;
        float sampleY = y * frequency * noiseScale;

        int ix = static_cast<int>(std::floor(sampleX));
        int iy = static_cast<int>(std::floor(sampleY));

        if (ix < 0 or ix >= gridSize.rows - 1 or iy < 0 or iy >= gridSize.cols - 1)
        {
            continue;
        }

        std::array<Vector, 4> offsets = findOffsets(sampleX, sampleY);
        std::array<float, 4> dotProducts = {
            dot(offsets[0], noiseGrid[ix][iy]),
            dot(offsets[1], noiseGrid[ix + 1][iy]),
            dot(offsets[2], noiseGrid[ix][iy + 1]),
            dot(offsets[3], noiseGrid[ix + 1][iy + 1]),
        };

        // cubic interpolation
        float sx = smoothstep(0.0f, 1.0f, offsets[0].x);
        float sy = smoothstep(0.0f, 1.0f, offsets[0].y);

        float ix0 = dotProducts[0] * (1.0f - sx) + dotProducts[1] * sx;
        float ix1 = dotProducts[2] * (1.0f - sx) + dotProducts[3] * sx;
        float value = ix0 * (1.0f - sy) + ix1 * sy;

        total += value * amplitude;
        maxAmplitude += amplitude;

        amplitude *= 0.5f;  // each additional octave should count for half as much as the previous one 
        frequency *= 2.0f;  // octaves, by definition, are double the frequency
    }

    return (maxAmplitude > 0) ? (total / maxAmplitude) : 0.0f; // normalize to [-1,1]
}

// idea is to create noise values, [-1, 1], and then use a threshold, T, to determine what's 'land'
// and what's 'water'. Anything lower than T is water; anything higher, land.
void PerlinNoise::generateNoise(void)
{
    const float T = -0.05f; // threshold for water vs land

    for (int r = 0; r < gridSize.rows - 1; ++r)
    {
        for (int c = 0; c < gridSize.cols - 1; ++c)
        {
            // use the center of the tile as the candidate point
            float x = r + 0.5f;
            float y = c + 0.5f;

            // compute noise value with multiple octaves
            float value = addOctaves(x, y);

            // assign tile type based on threshold
            (*tiles)[r][c] = (value < T) ? TileType::Water : TileType::Grass;
        }
    }
}


