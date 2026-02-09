#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
#include <memory>

using TileGrid = std::vector<std::vector<int>>;
using GridPtr = std::shared_ptr<TileGrid>;

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

#endif