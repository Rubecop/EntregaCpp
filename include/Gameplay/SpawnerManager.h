#pragma once
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Gameplay/ObstacleSpawner.h>

class SpawnerManager
{
public:
    SpawnerManager(Zombie* player,
        float spawnInterval,
        const sf::Vector2f& obstacleSize,
        float switchInterval);

    ~SpawnerManager();

    void update(float deltaSeconds);

    void render(sf::RenderWindow& window);

    void handlePlayerCollision(const sf::FloatRect& playerBounds);
private:
    void chooseTwoActiveSpawners();
    std::vector<ObstacleSpawner*> m_spawners;
    float m_switchInterval;
    float m_switchElapsed;
};