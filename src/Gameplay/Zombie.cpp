#include <Gameplay/Zombie.h>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm> // <-- NECESARIO PARA std::clamp

bool Zombie::init(const ZombieDescriptor& zombieDescriptor)
{
	m_speed = zombieDescriptor.speed;
	return Enemy::init(zombieDescriptor);
}

void Zombie::update(float deltaMilliseconds)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_direction.x = -1.0f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_direction.x = 1.0f;
	}
	else
	{
		m_direction.x = .0f;
	}

	// Movimiento
	m_position.x += (m_direction.x * m_speed.x * deltaMilliseconds);
	m_position.y += (m_direction.y * m_speed.y * deltaMilliseconds);

	// Clamp horizontal (entre 500 y 1200)
	m_position.x = std::clamp(m_position.x, 500.f, 1200.f);

	Enemy::update(deltaMilliseconds);
}
