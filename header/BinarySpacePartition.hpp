#ifndef BINARYSPACEPARTITION_HPP
#define BINARYSPACEPARTITION_HPP

#include "SimpleRoom.hpp"
#include "BSPNode.hpp"

class BinarySpacePartition : public SimpleRoom
{
private:
    BSPNode* root;

    void splitHelper(BSPNode* node, bool splitVertical);
    Room createRoomInLeaf(const BSPNode* leaf);

public:
    BinarySpacePartition(int** tiles, int numRooms, Size minSize, Size maxSize, Size gridSize);

    void split(BSPNode* node);
    void createRoomsBSP(BSPNode* node);
    void connectBSPRooms();

    BSPNode* getRoot() { return root; }
};

#endif
