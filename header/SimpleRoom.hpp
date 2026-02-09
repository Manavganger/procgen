#ifndef SIMPLE_ROOM_HPP
#define SIMPLE_ROOM_HPP

#include "Common.hpp"
class SimpleRoom
{
    protected:
        GridPtr tiles; 
        std::vector<Room> rooms;
        const int numRooms;
        const Size minSize, maxSize, gridSize;

        void drawRoom(const Room&);
        bool checkCollision(const Room& newRoom);
        void drawCorridors(const Room& room1, const Room& room2);
        void connectRoomsPrims(void);

    public:
        SimpleRoom(GridPtr tiles, int numRooms, Size minSize, Size maxSize, Size gridSize);
        void createRooms(void);
};

#endif 