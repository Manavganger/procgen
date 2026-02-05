#include "../header/SimpleRoom.hpp"
#include <random>

// Constructor
SimpleRoom::SimpleRoom(int** tiles, int numRooms, Size minSize, Size maxSize, Size gridSize)
    : tiles(tiles), numRooms(numRooms), minSize(minSize), maxSize(maxSize), gridSize(gridSize)
{
    // leave empty 
}

bool SimpleRoom::checkCollision(const Room& newRoom)
{
    const Room& nr = newRoom;
    for (const auto& r : rooms)
    {
        bool overlap = !( 
            nr.xpos + nr.xlen + 1 < r.xpos or   
            nr.xpos > r.xpos + r.xlen + 1 or    
            nr.ypos + nr.ylen + 1 < r.ypos or 
            nr.ypos > r.ypos + r.ylen + 1          
        );

        if (overlap)
            return true;
    }
    return false;
}

void SimpleRoom::createRooms(void)
{
    for (int i = 0; i < numRooms; ++i)
    {
        Room currRoom{};
        do 
        {
            // generate room size in accordance to specification
            int xlen = rand() % (maxSize.cols - minSize.cols + 1) + minSize.cols;
            int ylen = rand() % (maxSize.rows - minSize.rows + 1) + minSize.rows;

            // superimpose room at arbitrary location
            int xpos = rand() % (gridSize.cols - xlen - 1) + 1;
            int ypos = rand() % (gridSize.rows - ylen - 1) + 1;

            // bounds checking 
            if ((xlen <= 0) or (xlen + xpos >= gridSize.cols) or (ylen <= 0) or (ylen + ypos >= gridSize.rows))
            {
                continue;
            }

            currRoom = Room{xlen, ylen, xpos, ypos};

        } while (checkCollision(currRoom));

        drawRoom(currRoom);
    }
}

void SimpleRoom::drawRoom(const Room& room)
{
    // can assume room will not exceed tiles buffer and will NOT collide/merge with any preexisting room
    // draw room on tile map, and add room to rooms vector

    // add to rooms
    rooms.push_back(room);

    // draw room
    for (int r = room.ypos; r < room.ypos + room.ylen; ++r)
    {
        for (int c = room.xpos; c < room.xpos + room.xlen; ++c)
        {
            tiles[r][c] = 1;
        }
    }
}