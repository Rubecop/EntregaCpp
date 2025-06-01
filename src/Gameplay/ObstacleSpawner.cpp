#include "Gameplay/ObstacleSpawner.h"
#include <Core/AssetManager.h>
#include <iostream>

ObstacleSpawner::ObstacleSpawner(Zombie* player,
    float spawnInterval,
    const sf::Vector2f& spawnPosition,
    const sf::Vector2f& obstacleSize,
    float initialOffset,
    bool isHardMode)
    : m_spawnInterval(spawnInterval),
    m_elapsedTime(initialOffset),
    m_enabled(true),
    m_spawnPosition(spawnPosition),
    player(player),
    m_obstacleSize(obstacleSize),
    m_isHardMode(isHardMode)
{
}

ObstacleSpawner::~ObstacleSpawner()
{
    for (auto* obs : m_obstacles)
        delete obs;
    m_obstacles.clear();

}

void ObstacleSpawner::update(float deltaSeconds)
{
    for (int i = static_cast<int>(m_obstacles.size()) - 1; i >= 0; --i)
    {
        Obstacle* obs = m_obstacles[i];
        obs->update(deltaSeconds);

        const sf::FloatRect bounds = obs->getBounds();
        if (bounds.top > 1500.f)
        {
            delete obs;
            m_obstacles.erase(m_obstacles.begin() + i);
        }
    }

    if (!m_enabled) { return; }
    m_elapsedTime += deltaSeconds;

    if (m_elapsedTime >= m_spawnInterval)
    {
        spawnObstacle();
        m_elapsedTime -= m_spawnInterval;
    }
}

void ObstacleSpawner::render(sf::RenderWindow& window)
{
    for (auto* obs : m_obstacles)
    {
        obs->render(window);
    }
}

void ObstacleSpawner::spawnObstacle()
{
    std::cout << "Spawning obstacle - hardMode: " << std::boolalpha << m_isHardMode << std::endl;

    sf::Texture* obstacleTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Obstacles/car2.png");

    if (m_isHardMode) 
    {
        Obstacle* newObs = new Obstacle(m_spawnPosition, m_obstacleSize, obstacleTexture,700.f);
        m_obstacles.push_back(newObs);
    }
    else
    { 
        Obstacle* newObs = new Obstacle(m_spawnPosition, m_obstacleSize, obstacleTexture, 450.f); 
        m_obstacles.push_back(newObs);
    }
}

void ObstacleSpawner::handlePlayerCollision(const sf::FloatRect& playerBounds)
{
    for (int i = static_cast<int>(m_obstacles.size()) - 1; i >= 0; --i)
    {
        Obstacle* obs = m_obstacles[i];
        if (obs->getBounds().intersects(playerBounds))
        {
            player->TakeDamage(1);
            delete obs;
            m_obstacles.erase(m_obstacles.begin() + i);
        }
    }
}

void ObstacleSpawner::resetTimer()
{
    m_elapsedTime = 0.f;
}