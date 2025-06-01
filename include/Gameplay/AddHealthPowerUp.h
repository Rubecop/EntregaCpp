#pragma once
#include <Gameplay/PowerUpBase.h>
class AddHealthPowerUp : public PowerUpBase
{
public:
    AddHealthPowerUp(Zombie* player, const sf::Vector2f& position);

    void onGrab() override;
};