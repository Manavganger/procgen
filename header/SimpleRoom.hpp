#ifndef SIMPLEROOM_HPP
#define SIMPLEROOM_HPP

#include "Size.hpp"
#include "Room.hpp"
#include <vector>

class SimpleRoom
{
    private:
        int** tiles;
        int numRooms;
        Size minSize;
        Size maxSize;
        std::vector<Room> rooms;

    public:
        SimpleRoom(int**);
};

#endif 