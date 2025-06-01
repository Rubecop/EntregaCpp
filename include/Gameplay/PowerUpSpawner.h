#pragma once
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Gameplay/Zombie.h"
#include "PowerUpBase.h"

class PowerUpSpawner
{
public:
    PowerUpSpawner(Zombie* player,
        float spawnInterval,
        float minX,
        float maxX,
        const sf::Vector2f& spawnPosition,
        const sf::Vector2f& coinSize,
        float initialOffset = 0.f);

    ~PowerUpSpawner();

    void update(float deltaSeconds);
    void render(sf::RenderWindow& window);

    void handlePlayerCollision(const sf::FloatRect& playerBounds);
    void resetTimer();

private:
    void spawnPowerUp();
private:
    Zombie* m_player;
    PowerUpBase* m_powerUp = nullptr;

    float m_spawnInterval;
    float m_elapsedTime;
    bool m_enabled;

    float m_minX;
    float m_maxX;

    std::vector<float> m_spawnPositionsX = { 550.f, 850.f, 1150.f };
    sf::Vector2f m_spawnPosition;
};