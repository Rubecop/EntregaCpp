#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class ManualMap
{
public:
    ManualMap();
    void render(sf::RenderWindow& window);

private:
    std::vector<sf::RectangleShape> m_tiles;
    sf::Texture* m_grassTexture;
    sf::Texture* m_roadTexture;
};
