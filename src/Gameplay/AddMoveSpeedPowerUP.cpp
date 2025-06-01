#include <Gameplay/AddMoveSpeedPowerUP.h>
#include <iostream>

AddMoveSpeedPowerUP::AddMoveSpeedPowerUP(Zombie* player, const sf::Vector2f& pos)
    : PowerUpBase(player, pos, "../Data/Images/Grabbables/PowerUpSpeed.png") {}

void AddMoveSpeedPowerUP::onGrab()
{
    std::cout << "¡PowerUp de curación recogido!\n";
    m_player->Heal(1);
}