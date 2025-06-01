#include <Core/AssetManager.h>
#include <Render/ManualMap.h>

ManualMap::ManualMap()
{
    m_grassTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Tiles/grass.png");
    m_roadTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Tiles/road.jpg");

    //GRASS TILES
    for (int row = 0; row < rows; ++row)
    {
        float yGrass = row * tileHeightGrass;

        for (int col = 0; col < cols; ++col)
        {
            sf::RectangleShape tile;
            tile.setSize({ tileWidthGrass, tileHeightGrass });
            tile.setPosition(col * tileWidthGrass, yGrass);
            tile.setTexture(m_grassTexture);
            m_grassTiles.push_back(tile);
        }
    }

    //ROAD TILES
    for (int row = 0; row < rows; ++row)
    {
        float yRoad = row * tileHeightRoad;
        float startX = 500.f;

        for (int i = 0; i < 3; ++i)
        {
            sf::RectangleShape tile;
            tile.setSize({ tileWidthRoad, tileHeightRoad });
            tile.setPosition(startX + i * tileWidthRoad, yRoad);
            tile.setTexture(m_roadTexture);
            m_roadTiles.push_back(tile);
        }
    }
}

void ManualMap::render(sf::RenderWindow & window)
{
    for (const auto& tile : m_grassTiles)
        window.draw(tile);

    for (const auto& tile : m_roadTiles)
        window.draw(tile);
}

void ManualMap::update(float dt)
{
    m_roadPosY += roadSpeed * dt;

    if (m_roadPosY >= tileHeightRoad)
        m_roadPosY -= tileHeightRoad;

    for (int i = 0; i < m_roadTiles.size(); ++i)
    {
        int row = i / 3;
        int col = i % 3;

        float x = 500.f + col * tileWidthRoad;
        float y = row * tileHeightRoad + m_roadPosY - tileHeightRoad;

        m_roadTiles[i].setPosition(x, y);
    }
}
