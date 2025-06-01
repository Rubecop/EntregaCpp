#include <Gameplay/AddMoveSpeedPowerUP.h>
#include <iostream>
#include <Core/AssetManager.h>

AddMoveSpeedPowerUP::AddMoveSpeedPowerUP(Zombie* player, const sf::Vector2f& position)
    : PowerUpBase(player, position, "../Data/Images/Grabbables/PowerUpSpeed.png"),
    m_player(player)
{
    m_duration = 10.f;
}

void AddMoveSpeedPowerUP::onGrab()
{
    m_active = true;
    m_elapsed = 0.f;

    m_originalSpeedX = m_player->getSpeed().x;

    sf::Vector2f boostedSpeed = m_player->getSpeed();
    boostedSpeed.x *= 1.5f;
    m_player->setSpeed(boostedSpeed);
}

void AddMoveSpeedPowerUP::update(float deltaTime)
{
    PowerUpBase::update(deltaTime);

    if (!m_active) return;

    m_elapsed += deltaTime;
    if (m_elapsed >= m_duration)
    {
        m_active = false;
        onExpire(); // nuevo método virtual opcional
    }
}

void AddMoveSpeedPowerUP::onExpire()
{
    sf::Vector2f currentSpeed = m_player->getSpeed();
    currentSpeed.x = m_originalSpeedX;
    m_player->setSpeed(currentSpeed);
}

