#pragma once
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Gameplay/Obstacle.h>

class ObstacleSpawner
{
public:
    ObstacleSpawner(float spawnInterval,
        const sf::Vector2f& spawnPosition,
        const sf::Vector2f& obstacleSize,
        float initialOffset = 0.f);

    ~ObstacleSpawner();
    void update(float deltaSeconds);

    void render(sf::RenderWindow& window);

    void setEnabled(bool enable) { m_enabled = enable; }

    bool isEnabled() const { return m_enabled; }

    void handlePlayerCollision(const sf::FloatRect& playerBounds);

    void resetTimer();
private:
    void spawnObstacle();

    std::vector<Obstacle*> m_obstacles;
    float m_spawnInterval; 
    float m_elapsedTime;  
    bool m_enabled;      

    sf::Vector2f m_spawnPosition;
    sf::Vector2f m_obstacleSize;
    sf::Texture m_obstacleTexture;
};