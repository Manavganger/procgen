#include <SFML/Graphics.hpp>
#include "../header/SimpleRoom.hpp"
#include "../header/BinarySpacePartition.hpp"

sf::Color valueToColorMap(int value)
{
    switch (value)
    {
        case 1: return sf::Color(150, 150, 150); // open space
        default: return sf::Color(70, 70, 70);   // wall
    }
}

int main()
{
    const int tileSize = 10;
    const int gap = 1;
    const int margin = 10;
    const int cols = 120;
    const int rows = 75;

    const int windowWidth  = margin * 2 + cols * tileSize + (cols - 1) * gap;
    const int windowHeight = margin * 2 + rows * tileSize + (rows - 1) * gap;

    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}), "Tile Grid");

    int tiles[rows][cols] = {}; // zero-init
    int* tilesPtr[rows];
    for (int i = 0; i < rows; ++i)
        tilesPtr[i] = tiles[i];

    // procgen logic goes here
    BinarySpacePartition bsp(tilesPtr, 10, {5,5}, {13,13}, {rows, cols});

    BSPNode* root = bsp.getRoot(); 
    bsp.split(root);
    bsp.createRoomsBSP(root);
    bsp.connectBSPRooms();
    //procgen logic end

    sf::RectangleShape tile({tileSize, tileSize});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color(30,30,30));

        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < cols; ++x)
            {
                tile.setFillColor(valueToColorMap(tiles[y][x]));
                tile.setPosition({
                    static_cast<float>(margin + x*(tileSize+gap)),
                    static_cast<float>(margin + y*(tileSize+gap))
                });
                window.draw(tile);
            }
        }

        window.display();
    }

    return 0;
}
