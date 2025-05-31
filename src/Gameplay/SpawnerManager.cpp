#include "Gameplay/SpawnerManager.h"
#include <cstdlib>   // srand, rand
#include <ctime>     // time

SpawnerManager::SpawnerManager(float spawnInterval,
    const sf::Vector2f& obstacleSize,
    float switchInterval)
    : m_switchInterval(switchInterval),
    m_switchElapsed(0.f)
{
    // Inicializamos la semilla de rand() solo una vez
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Creamos los tres spawners en sus posiciones fijas (X=0, Y=400/600/800)
    // Les pasamos spawnInterval y obstacleSize, sin desfase inicial.
    m_spawners.push_back(new ObstacleSpawner(spawnInterval, { 550.f, -250.f }, obstacleSize, 0.f));
    m_spawners.push_back(new ObstacleSpawner(spawnInterval, { 850.f, -250.f }, obstacleSize, 0.f));
    m_spawners.push_back(new ObstacleSpawner(spawnInterval, { 1150.f , -250.f }, obstacleSize, 0.f));

    // Antes de arrancar, elegimos aleatoriamente cuáles dos spawners estarán activos
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
    // 1) Actualizamos cada spawner (internamente aplica spawn solo si está habilitado, pero siempre mueve sus obstáculos)
    for (auto* sp : m_spawners)
    {
        sp->update(deltaSeconds);
    }

    // 2) Avanzamos el cronómetro de “cambio de pareja activa”
    m_switchElapsed += deltaSeconds;
    if (m_switchElapsed >= m_switchInterval)
    {
        chooseTwoActiveSpawners();
        m_switchElapsed -= m_switchInterval;
        // Si prefieres que no se “acumule” el exceso, podrías usar “m_switchElapsed = 0.0f;”
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
    // Desactivar todos inicialmente
    for (auto* sp : m_spawners) 
    {
        sp->setEnabled(false);
        sp->resetTimer();
    }
    // Elegimos dos índices distintos en [0, 1, 2]
    int first = std::rand() % 3;           // valor aleatorio en {0,1,2}
    int second;
    do {
        second = std::rand() % 3;
    } while (second == first);

    // Activamos solo esos dos
    m_spawners[first]->setEnabled(true);
    m_spawners[second]->setEnabled(true);

    // El tercero queda desactivado.
    // (Si quisieras saber cuál es el tercero para debug: “third = 3 – first – second;”)
}
void SpawnerManager::handlePlayerCollision(const sf::FloatRect& playerBounds)
{
    for (auto* sp : m_spawners)
    {
        sp->handlePlayerCollision(playerBounds);
    }
}