#pragma once
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Gameplay/Zombie.h"
#include "Gameplay/Coin.h"

class CoinSpawner
{
public:
    CoinSpawner(Zombie* player,
        float spawnInterval,
        float minX,
        float maxX,
        const sf::Vector2f& spawnPosition,
        const sf::Vector2f& coinSize,
        float initialOffset = 0.f);
    ~CoinSpawner();

    void update(float deltaSeconds);
    void render(sf::RenderWindow& window);

    void handlePlayerCollision(const sf::FloatRect& playerBounds);
    void resetTimer();

private:
    void spawnSingleCoin(int index);

private:
    Zombie* m_player;

    float m_singleSpawnInterval = 0.3f;
    float m_singleElapsedTime = 0.f;
    int m_coinsSpawnedInBatch = 0;

    float m_spawnInterval;
    float m_elapsedTime;
    bool m_enabled;

    float m_minX;
    float m_maxX;

    std::vector<Coin*> m_coins;
    std::vector<float> m_spawnPositionsX = { 550.f, 850.f, 1150.f };

    sf::Vector2f m_spawnPosition;
    sf::Vector2f m_coinSize;
    sf::Vector2f m_currentBatchSpawnPos;
};