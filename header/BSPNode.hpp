#ifndef BSPNODE_HPP
#define BSPNODE_HPP

struct BSPNode
{
    int xlen, ylen;
    int xpos, ypos;     // top left of partition
    
    BSPNode* left, right;
    Room room;          // does partition contain room (leaf nodes only)
    bool hasRoom;       // only true for leaf nodes

    BSPNode(int x, int y, int w, int h)
        : xpos(x), ypos(y), xlen(w), ylen(h), left(nullptr), right(nullptr), hasRoom(false)
    {
        
    }
};

#endif 