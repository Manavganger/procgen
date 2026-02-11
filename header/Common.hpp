#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
#include <memory>
#include <cstdlib> 
#include <ctime>   
// does NOT specify location, only size
struct Size
{
    int rows, cols;
};

struct Vector
{
    float x, y;
};

struct Room
{
    int xlen, ylen;
    int xpos, ypos;      // position defined as top left tile
};

enum class TileType
{
    Wall = 0,
    Open = 1,
    Water = 2, 
    Grass = 3
};

using TileGrid = std::vector<std::vector<TileType>>;
using GridPtr = std::shared_ptr<TileGrid>;
using PerlinGrid = std::vector<std::vector<Vector>>;

#endif