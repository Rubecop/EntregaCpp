#pragma once
#include <Gameplay/PowerUpBase.h>
class AddMoveSpeedPowerUP : public PowerUpBase
{
public:
    AddMoveSpeedPowerUP(Zombie* player, const sf::Vector2f& position);

    void onGrab() override;
};