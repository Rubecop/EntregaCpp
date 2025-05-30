#include "Gameplay/ObstacleSpawner.h"
#include <cstdlib> // for rand

ObstacleSpawner::ObstacleSpawner(float spawnInterval, const sf::Vector2f& spawnPosition, const sf::Vector2f& obstacleSize)
    : m_spawnInterval(spawnInterval),
    m_elapsedTime(0.f),
    m_spawnPosition(spawnPosition),
    m_obstacleSize(obstacleSize)
{
}

ObstacleSpawner::~ObstacleSpawner()
{
    for (auto* obstacle : m_obstacles)
        delete obstacle;
    m_obstacles.clear();
}

void ObstacleSpawner::update(float deltaSeconds)
{
    m_elapsedTime += deltaSeconds;

    if (m_elapsedTime >= m_spawnInterval)
    {
        spawnObstacle();
        m_elapsedTime = 0.f;
    }

    for (auto* obstacle : m_obstacles)
    {
        obstacle->update(deltaSeconds);
    }
}

void ObstacleSpawner::render(sf::RenderWindow& window)
{
    for (auto* obstacle : m_obstacles)
    {
        obstacle->render(window);
    }
}

void ObstacleSpawner::spawnObstacle()
{
    Obstacle* obstacle = new Obstacle(m_spawnPosition, m_obstacleSize);
    m_obstacles.push_back(obstacle);
}