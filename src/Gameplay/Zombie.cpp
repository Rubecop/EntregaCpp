#include <Gameplay/Zombie.h>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>

bool Zombie::init(const ZombieDescriptor& zombieDescriptor)
{
	m_speed = zombieDescriptor.speed;
	maxHealth = 3;
	currentHealth = maxHealth;
	currentCoins = 0;
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

void Zombie::AddCoins(int amount)
{
	currentCoins += amount;
}

void Zombie::TakeDamage(int amount) 
{
	currentHealth -= amount;
	if (currentHealth <= 0) {
		// GAMEOVER Y RECARGAR MAINMENU
	}
}

void Zombie::Heal(int amount)
{
	if (currentHealth > maxHealth) 
	{
		currentHealth += amount;
	}
}
int Zombie::GetCoins()
{
	return currentCoins;
}
int Zombie::GetHealth()
{
	return currentHealth;
}
