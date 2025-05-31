#include <Core/AssetManager.h> // o usa loadFromFile directamente
#include <Render/ManualMap.h>

ManualMap::ManualMap()
{
    const float tileWidthGrass = 100.f;
    const float tileHeightGrass = 100.f;

    const float tileWidthRoad =300.f;
    const float tileHeightRoad = 100.f;

    const int rows = 16;   // altura del mapa en tiles
    const int cols = 20;  // ancho del mapa en tiles

    // Cargamos texturas (puedes usar AssetManager si tienes uno)
    m_grassTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Tiles/grass.png");
    m_roadTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Tiles/road.jpg");

    // 1. GRASS: cubrir toda el área base
    for (int row = 0; row < rows; ++row)
    {
        float yGrass = row * tileHeightGrass;

        for (int col = 0; col < cols; ++col)
        {
            sf::RectangleShape tile;
            tile.setSize({ tileWidthGrass, tileHeightGrass });
            tile.setPosition(col * tileWidthGrass, yGrass);
            tile.setTexture(m_grassTexture);
            m_tiles.push_back(tile);
        }
    }

    // 2. ROAD: por encima, desde x = 600, a lo largo de las mismas filas
    for (int row = 0; row < rows; ++row)
    {
        float yRoad = row * tileHeightRoad;

        // Coloca 3 tiles de carretera, comenzando desde x = 600
        float startX = 500.f;

        for (int i = 0; i < 3; ++i)
        {
            sf::RectangleShape tile;
            tile.setSize({ tileWidthRoad, tileHeightRoad });

            // Road se solapa sobre la hierba
            tile.setPosition(startX + i * tileWidthRoad, yRoad);
            tile.setTexture(m_roadTexture);
            m_tiles.push_back(tile);
        }
    }
}

void ManualMap::render(sf::RenderWindow & window)
{
    for (const auto& tile : m_tiles)
        window.draw(tile);
}