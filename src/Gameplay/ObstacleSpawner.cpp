#include "Gameplay/ObstacleSpawner.h"
#include <Core/AssetManager.h>

ObstacleSpawner::ObstacleSpawner(Zombie* player,
    float spawnInterval,
    const sf::Vector2f& spawnPosition,
    const sf::Vector2f& obstacleSize,
    float initialOffset)
    : m_spawnInterval(spawnInterval),
    m_elapsedTime(initialOffset),
    m_enabled(true),            // por defecto arrancamos habilitados
    m_spawnPosition(spawnPosition),
    player(player),
    m_obstacleSize(obstacleSize)
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
    // 1) Actualizamos la posición de TODOS los obstáculos generados hasta ahora
    for (auto* obs : m_obstacles)
    {
        obs->update(deltaSeconds);
    }

    // 2) Si este spawner está "habilitado", avanzamos su temporizador y spawneamos cuando toque
    if (!m_enabled)
        return;

    m_elapsedTime += deltaSeconds;

    // Si hemos superado el intervalo, generamos uno nuevo y descontamos ese intervalo
    if (m_elapsedTime >= m_spawnInterval)
    {
        spawnObstacle();
        m_elapsedTime -= m_spawnInterval;
        // (si deltaSeconds > spawnInterval, en un frame muy grande
        //  quizá deba usarse while(m_elapsedTime >= m_spawnInterval))
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
    sf::Texture* obstacleTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Obstacles/car2.png");
    Obstacle* newObs = new Obstacle(m_spawnPosition, m_obstacleSize, obstacleTexture);
    m_obstacles.push_back(newObs);
}

void ObstacleSpawner::handlePlayerCollision(const sf::FloatRect& playerBounds)
{
    // Recorremos de atrás hacia adelante para poder borrar elementos sin invalidar índices
    for (int i = static_cast<int>(m_obstacles.size()) - 1; i >= 0; --i)
    {
        Obstacle* obs = m_obstacles[i];
        if (obs->getBounds().intersects(playerBounds))
        {
            // Si hay colisión: lo borramos de la memoria y del vector
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