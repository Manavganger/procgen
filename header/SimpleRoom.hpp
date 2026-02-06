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
        Size gridSize;
        std::vector<Room> rooms;

        void drawRoom(const Room&);
        bool checkCollision(const Room& newRoom);
        void drawCorridors(const Room& room1, const Room& room2);

    public:
        SimpleRoom(int** tiles, int numRooms, Size minSize, Size maxSize, Size gridSize);
        void createRooms(void);
};

#endif 