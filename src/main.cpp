#include <SFML/Graphics.hpp>

int main()
{
    const int tileSize = 20;
    const int cols = 10;
    const int rows = 10;

    sf::RenderWindow window(
        sf::VideoMode({cols * tileSize, rows * tileSize}),
        "Tile Grid"
    );

    sf::RectangleShape tile({tileSize, tileSize});
    tile.setFillColor(sf::Color(98, 98, 98, 255));

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);

        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < cols; ++x)
            {
                tile.setPosition({
                    static_cast<float>(x * tileSize),
                    static_cast<float>(y * tileSize)
				});
                window.draw(tile);
            }
        }

        window.display();
    }

    return 0;
}
