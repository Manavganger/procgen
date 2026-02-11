#ifndef BINARY_SPACE_PARTITION_HPP
#define BINARY_SPACE_PARTITION_HPP

#include "SimpleRoom.hpp"
#include "BSPNode.hpp"
#include <algorithm>

class BinarySpacePartition : public SimpleRoom
{
private:
    BSPNode* root;

    void splitHelper(BSPNode* node, bool splitVertical);
    Room createRoomInLeaf(const BSPNode* leaf);

public:
    BinarySpacePartition(GridPtr tiles, int numRooms, Size minSize, Size maxSize, Size gridSize);

    void split(BSPNode* node);
    void createRoomsBSP(BSPNode* node);
    void connectBSPRooms();

    BSPNode* getRoot() { return root; }
};

#endif
