#pragma once
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Gameplay/Obstacle.h>

class ObstacleSpawner
{
public:
    ObstacleSpawner(float spawnInterval, const sf::Vector2f& spawnPosition, const sf::Vector2f& obstacleSize);
    ~ObstacleSpawner();

    void update(float deltaSeconds);
    void render(sf::RenderWindow& window);

private:
    void spawnObstacle();

    std::vector<Obstacle*> m_obstacles;
    float m_spawnInterval;
    float m_elapsedTime;

    sf::Vector2f m_spawnPosition;
    sf::Vector2f m_obstacleSize;
};