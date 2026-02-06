#ifndef BINARYSPACEPARTITION_HPP
#define BINARYSPACEPARTITION_HPP
#include "SimpleRoom.hpp"

class BinarySpacePartition: public SimpleRoom
{
    public:
        BinarySpacePartition(int** tiles, int numRooms, Size minSize, Size maxSize, Size gridSize);
};

#endif