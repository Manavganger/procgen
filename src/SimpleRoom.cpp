#include "../header/SimpleRoom.hpp"
#include <cstdlib> 
#include <ctime>   

// Constructor
SimpleRoom::SimpleRoom(GridPtr& tiles, const int numRooms, const Size minSize, const Size maxSize, const Size gridSize)
    : tiles(tiles), numRooms(numRooms), minSize(minSize), maxSize(maxSize), gridSize(gridSize)
{
    std::srand(static_cast<unsigned int>(std::time(0)));
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
            ++attempts;
            if (attempts >= 100000) return;

            int xlen = rand() % (maxSize.cols - minSize.cols + 1) + minSize.cols;
            int ylen = rand() % (maxSize.rows - minSize.rows + 1) + minSize.rows;
            int xpos = rand() % (gridSize.cols - xlen - 1) + 1;
            int ypos = rand() % (gridSize.rows - ylen - 1) + 1;

            if ((xlen <= 0) or (xlen + xpos >= gridSize.cols) or (ylen <= 0) or (ylen + ypos >= gridSize.rows))
                continue;

            currRoom = Room{xlen, ylen, xpos, ypos};

        } while (checkCollision(currRoom));

        drawRoom(currRoom);
    }

    if (!rooms.empty()) {
        connectRoomsPrims();
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
            (*tiles)[r][c] = 1;
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
        (*tiles)[y1][c] = 1;

    for (int r = std::min(y1, y2); r <= std::max(y1, y2); ++r)
        (*tiles)[r][x2] = 1;
}


// Note: using prims algo will ensure no cycles in the 'graph'. This means that the end result will have lots of "choke points"
// To avoid this, simple connect rooms with L corridors as they appear in the rooms vector
void SimpleRoom::connectRoomsPrims() 
{
    int n = rooms.size();
    std::vector<bool> reached(n, false);
    std::vector<double> minDist(n, 1e18);
    std::vector<int> parent(n, -1);

    minDist[0] = 0;

    for (int i = 0; i < n; ++i)
    {
        int u = -1;
        for (int j = 0; j < n; ++j) 
        {
            if (!reached[j] and (u == -1 or minDist[j] < minDist[u])) u = j;
        }

        if (u == -1) break;
        reached[u] = true;

        if (parent[u] != -1)
        {
            drawCorridors(rooms[parent[u]], rooms[u]);
        }

        for (int v = 0; v < n; ++v) 
        {
            if (!reached[v]) 
            {
                // calculate centers
                int x1 = rooms[u].xpos + rooms[u].xlen / 2;
                int y1 = rooms[u].ypos + rooms[u].ylen / 2;
                int x2 = rooms[v].xpos + rooms[v].xlen / 2;
                int y2 = rooms[v].ypos + rooms[v].ylen / 2;

                // manhattan distnace
                int dist = std::abs(x1 - x2) + std::abs(y1 - y2);

                if (dist < minDist[v]) 
                {
                    minDist[v] = (double)dist;
                    parent[v] = u;
                }
            }
        }
    }
}