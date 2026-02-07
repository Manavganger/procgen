#ifndef BSPNODE_HPP
#define BSPNODE_HPP

#include "SimpleRoom.hpp"

struct BSPNode
{
    int xpos, ypos;    // top-left corner of partition
    int xlen, ylen;

    BSPNode* left;
    BSPNode* right;

    Room room;         
    bool hasRoom;      // true only for leaf nodes

    BSPNode(int x, int y, int w, int h)
        : xpos(x), ypos(y), xlen(w), ylen(h),
          left(nullptr), right(nullptr), hasRoom(false) {}
};

#endif
