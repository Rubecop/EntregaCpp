#include "Gameplay/SpawnerManager.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

SpawnerManager::SpawnerManager(Zombie* player,
    float spawnInterval,
    const sf::Vector2f& obstacleSize,
    float switchInterval,
    bool isHardmode)
    : m_switchInterval(switchInterval),
    m_isHardMode(isHardmode),
    m_switchElapsed(0.f)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "Spawning spawners - hardMode: " << std::boolalpha << m_isHardMode << std::endl;

    // There must be a better way of implementing this, at the time, I thought it was the best idea since I needed 2 simultaneous spawns

    m_spawners.push_back(new ObstacleSpawner(player,spawnInterval, { 550.f, -350.f }, obstacleSize, 0.f, m_isHardMode));
    m_spawners.push_back(new ObstacleSpawner(player,spawnInterval, { 850.f, -350.f }, obstacleSize, 0.f, m_isHardMode));
    m_spawners.push_back(new ObstacleSpawner(player, spawnInterval, { 1150.f , -350.f }, obstacleSize, 0.f, m_isHardMode));

    chooseTwoActiveSpawners();
}

SpawnerManager::~SpawnerManager()
{
    for (auto* sp : m_spawners)
        delete sp;
    m_spawners.clear();
}

void SpawnerManager::update(float deltaSeconds)
{
    for (auto* sp : m_spawners)
    {
        sp->update(deltaSeconds);
    }

    m_switchElapsed += deltaSeconds;
    if (m_switchElapsed >= m_switchInterval)
    {
        chooseTwoActiveSpawners();
        m_switchElapsed -= m_switchInterval;
    }
}

void SpawnerManager::render(sf::RenderWindow& window)
{
    for (auto* sp : m_spawners)
    {
        sp->render(window);
    }
}

void SpawnerManager::chooseTwoActiveSpawners()
{
    for (auto* sp : m_spawners) 
    {
        sp->setEnabled(false);
        sp->resetTimer();
    }

    int first = std::rand() % 3;
    int second;
    do {
        second = std::rand() % 3;
    } while (second == first);

    m_spawners[first]->setEnabled(true);
    m_spawners[second]->setEnabled(true);

}
void SpawnerManager::handlePlayerCollision(const sf::FloatRect& playerBounds)
{
    for (auto* sp : m_spawners)
    {
        sp->handlePlayerCollision(playerBounds);
    }
}