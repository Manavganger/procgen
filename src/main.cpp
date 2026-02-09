#include <SFML/Graphics.hpp>
#include "../header/SimpleRoom.hpp"

sf::Color valueToColorMap(int value)
{
    switch (value)
    {
        case 1: return sf::Color(150, 150, 150);	//open space
        default: return sf::Color(70, 70, 70);		//default should be a wall, not an open space
    }
}

int main()
{
    const int tileSize = 10;
    const int gap = 1;
    const int margin = 10; // can remove later
    const int cols = 120;
    const int rows = 75;

    const int windowWidth  = margin * 2 + cols * tileSize + (cols - 1) * gap;
    const int windowHeight = margin * 2 + rows * tileSize + (rows - 1) * gap;

    sf::RenderWindow window(
        sf::VideoMode({windowWidth, windowHeight}),
        "Tile Grid"
    );

    auto tiles = std::make_shared<std::vector<std::vector<int>>>(
        rows, std::vector<int>(cols, 0)
    );

    //procgen logic goes here
    SimpleRoom sr(tiles, 65, {5, 5}, {13, 13}, {rows, cols});
    sr.createRooms();

    sf::RectangleShape tile({tileSize, tileSize});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

		// clear, draw, display loop

        window.clear(sf::Color(30, 30, 30));

        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < cols; ++x)
            {
                tile.setFillColor(valueToColorMap((*tiles)[y][x]));

				// set position based on top left corner 
                tile.setPosition({
                    static_cast<float>(margin + x * (tileSize + gap)),
                    static_cast<float>(margin + y * (tileSize + gap))
                });

                window.draw(tile);
            }
        }

        window.display();
    }

    return 0;
}