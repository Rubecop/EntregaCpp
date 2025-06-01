#include "Gameplay/PowerUpSpawner.h"
#include "Gameplay/AddHealthPowerUp.h"
#include "Gameplay/AddMoveSpeedPowerUp.h"
#include <cstdlib>
#include <ctime>

PowerUpSpawner::PowerUpSpawner(Zombie* player, float spawnInterval, float minX, float maxX, const sf::Vector2f& spawnPosition, const sf::Vector2f& coinSize, float initialOffset)
    : m_player(player)
    , m_spawnInterval(spawnInterval)
    , m_elapsedTime(initialOffset)
    , m_enabled(true)
    , m_minX(minX)
    , m_maxX(maxX)
    , m_spawnPosition(spawnPosition)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

PowerUpSpawner::~PowerUpSpawner()
{
    if (m_powerUp)
        delete m_powerUp;
}

void PowerUpSpawner::update(float deltaSeconds)
{
    m_elapsedTime += deltaSeconds;

    if (!m_enabled)
        return;

    if (m_powerUp)
    {
        m_powerUp->update(deltaSeconds);

        if (m_powerUp->getBounds().top > 1500)
        {
            delete m_powerUp;
            m_powerUp = nullptr;
        }
    }

    if (!m_powerUp && m_elapsedTime >= m_spawnInterval)
    {
        spawnPowerUp();
        m_elapsedTime = 0.f;
    }
}

void PowerUpSpawner::render(sf::RenderWindow& window)
{
    if (m_powerUp)
        m_powerUp->render(window);
}

void PowerUpSpawner::handlePlayerCollision(const sf::FloatRect& playerBounds)
{
    if (m_powerUp && m_powerUp->getBounds().intersects(playerBounds))
    {
        m_powerUp->onGrab();
        delete m_powerUp;
        m_powerUp = nullptr;
    }
}

void PowerUpSpawner::resetTimer()
{
    m_elapsedTime = 0.f;
}

void PowerUpSpawner::spawnPowerUp()
{
    float xPos = m_minX + static_cast<float>(rand()) / RAND_MAX * (m_maxX - m_minX);
    sf::Vector2f pos(xPos,-250.f);

    int type = rand() % 2;
    switch (type)
    {
    case 0:
        m_powerUp = new AddHealthPowerUp(m_player, pos);
        break;
    case 1:
        m_powerUp = new AddMoveSpeedPowerUP(m_player, pos);
        break;
    default:
        break;
    }
}