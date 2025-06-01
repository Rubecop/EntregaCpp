#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class ManualMap
{
public:
    ManualMap();

    void render(sf::RenderWindow& window);
    void update(float dt);
private:
 
    const float tileWidthGrass = 100.f;
    const float tileHeightGrass = 100.f;
    const float tileWidthRoad = 300.f;
    const float tileHeightRoad = 300.f;

    float m_roadPosY = -tileHeightRoad;

    const float windowHeight = 600.f;
    const float roadSpeed = 150.f;
    const int rows = 20;
    const int cols = 20;

    std::vector<sf::RectangleShape> m_tiles;

    sf::Texture* m_grassTexture;
    sf::Texture* m_roadTexture;
    std::vector<sf::RectangleShape> m_grassTiles;
    std::vector<sf::RectangleShape> m_roadTiles;
};
