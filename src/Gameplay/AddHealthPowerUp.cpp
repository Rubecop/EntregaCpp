#include <Gameplay/AddHealthPowerUp.h>
#include <iostream>

AddHealthPowerUp::AddHealthPowerUp(Zombie* player, const sf::Vector2f& pos)
    : PowerUpBase(player, pos, "../Data/Images/Grabbables/HealthPowerUp.png") {}

void AddHealthPowerUp::onGrab()
{
    std::cout << "¡PowerUp de curación recogido!\n";
    m_player->Heal(1); 
}