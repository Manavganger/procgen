#ifndef SIMPLEROOM_HPP
#define SIMPLEROOM_HPP

#include "Size.hpp"
#include "Room.hpp"
#include <vector>

class SimpleRoom
{
    protected:
        int** tiles;
        std::vector<Room> rooms;
        const int numRooms;
        const Size minSize, maxSize, gridSize;

        void drawRoom(const Room&);
        bool checkCollision(const Room& newRoom);
        void drawCorridors(const Room& room1, const Room& room2);
        void connectRoomsPrims(void);

    public:
        SimpleRoom(int** tiles, int numRooms, Size minSize, Size maxSize, Size gridSize);
        void createRooms(void);
};

#endif 