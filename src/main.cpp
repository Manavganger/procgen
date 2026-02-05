#include <SFML/Graphics.hpp>

int main()
{
    const int tileSize = 30;
    const int gap = 4;        // space between tiles
    const int margin = 10;    // space around the grid, can remove later
    const int cols = 20;
    const int rows = 20;

    const int windowWidth  = margin * 2 + cols * tileSize + (cols - 1) * gap;
    const int windowHeight = margin * 2 + rows * tileSize + (rows - 1) * gap;

    sf::RenderWindow window(
        sf::VideoMode({windowWidth, windowHeight}),
        "Tile Grid"
    );

    sf::RectangleShape tile({tileSize, tileSize});
    tile.setFillColor(sf::Color(98, 98, 98));

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

		// CLEAR DRAW DISPLAY LOOP
        window.clear(sf::Color(30, 30, 30));

        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < cols; ++x)
            {
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
