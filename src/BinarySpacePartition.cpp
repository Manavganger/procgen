#include "../header/BinarySpacePartition.hpp"


BinarySpacePartition::BinarySpacePartition(GridPtr tiles, int numRooms, Size minSize, Size maxSize, Size gridSize)
    : SimpleRoom(tiles, numRooms, minSize, maxSize, gridSize)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    root = new BSPNode(0, 0, gridSize.cols, gridSize.rows); // full grid
}

void BinarySpacePartition::split(BSPNode* node)
{
    if (!node) return;

    const int MIN_COLS = minSize.cols + 2;
    const int MIN_ROWS = minSize.rows + 2;

    if (node->xlen < 2 * MIN_COLS and node->ylen < 2 * MIN_ROWS)
        return; // cannot split further

    bool splitVertical;

    if (node->xlen >= 2 * MIN_COLS and node->ylen >= 2 * MIN_ROWS)
        splitVertical = rand() % 2;
    else if (node->xlen >= 2 * MIN_COLS)
        splitVertical = true;
    else
        splitVertical = false;

    splitHelper(node, splitVertical);

    if (node->left)  split(node->left);
    if (node->right) split(node->right);
}

void BinarySpacePartition::splitHelper(BSPNode* node, bool splitVertical)
{
    int minOffset = splitVertical ? minSize.cols + 2 : minSize.rows + 2;
    int maxOffset = splitVertical ? node->xlen - minOffset : node->ylen - minOffset;

    if (maxOffset <= minOffset)
    {
        node->left = nullptr;
        node->right = nullptr;
        return;
    }

    int offset = rand() % (maxOffset - minOffset + 1) + minOffset;

    node->left = new BSPNode(
        node->xpos,
        node->ypos,
        splitVertical ? offset : node->xlen,
        splitVertical ? node->ylen : offset
    );

    node->right = new BSPNode(
        splitVertical ? node->xpos + offset : node->xpos,
        splitVertical ? node->ypos : node->ypos + offset,
        splitVertical ? node->xlen - offset : node->xlen,
        splitVertical ? node->ylen : node->ylen - offset
    );
}

Room BinarySpacePartition::createRoomInLeaf(const BSPNode* leaf)
{
    int maxXLen = std::min(leaf->xlen - 2, maxSize.cols);
    int maxYLen = std::min(leaf->ylen - 2, maxSize.rows);

    int roomXLen = minSize.cols + (maxXLen > minSize.cols ? rand() % (maxXLen - minSize.cols + 1) : 0);
    int roomYLen = minSize.rows + (maxYLen > minSize.rows ? rand() % (maxYLen - minSize.rows + 1) : 0);

    int xposMax = leaf->xlen - roomXLen - 1;
    int yposMax = leaf->ylen - roomYLen - 1;

    int xpos = leaf->xpos + 1 + (xposMax > 0 ? rand() % xposMax : 0);
    int ypos = leaf->ypos + 1 + (yposMax > 0 ? rand() % yposMax : 0);

    return Room{roomXLen, roomYLen, xpos, ypos};
}

void BinarySpacePartition::createRoomsBSP(BSPNode* node)
{
    if (!node) return;

    if (!node->left and !node->right)
    {
        Room room = createRoomInLeaf(node);
        drawRoom(room);
        node->room = room;
        node->hasRoom = true;
    }
    else
    {
        createRoomsBSP(node->left);
        createRoomsBSP(node->right);
    }
}

// could have much more simply made connectRoomsPrims a friend function instead of making a wrapper
void BinarySpacePartition::connectBSPRooms()
{
    connectRoomsPrims();
}
