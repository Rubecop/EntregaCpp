#pragma once
#include <Gameplay/PowerUpBase.h>
#include <Gameplay/Zombie.h>

class AddMoveSpeedPowerUP : public PowerUpBase
{
public:
    AddMoveSpeedPowerUP(Zombie* player, const sf::Vector2f& position);

    void onGrab() override;

    void update(float deltaTime) override;

    void onExpire();
private:
    float m_duration = 0.f;
    float m_elapsed = 0.f;
    bool m_active = false;

    Zombie* m_player;
    float m_originalSpeedX = 0.f;

};