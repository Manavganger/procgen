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
        int attempts = 0;
        do 
        {
            // if too many attempts, early return to prevent infinite loop
            ++attempts;
            if (attempts >= 100000) return;

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
    
    for (size_t i = 1; i < rooms.size(); ++i)
    {
        drawCorridors(rooms[i - 1], rooms[i]);
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

void SimpleRoom::drawCorridors(const Room& room1, const Room& room2)
{
    int x1 = room1.xpos + room1.xlen / 2;
    int y1 = room1.ypos + room1.ylen / 2;
    int x2 = room2.xpos + room2.xlen / 2;
    int y2 = room2.ypos + room2.ylen / 2;

    for (int c = std::min(x1, x2); c <= std::max(x1, x2); ++c)
        tiles[y1][c] = 1;

    for (int r = std::min(y1, y2); r <= std::max(y1, y2); ++r)
        tiles[r][x2] = 1;
}