#include <Gameplay/Zombie.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>
#include <Core/AssetManager.h>
#include <iostream>

Zombie::Zombie()
{
}

bool Zombie::init()
{
	currentHealth = maxHealth;
	currentCoins = 0;
	m_texture = AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/zombie1.png");

	if (!m_texture) {
		std::cerr << "Error: Couldn't change texture zombie.png\n";
		return false;
	}

	m_sprite.setTexture(*m_texture);
	m_sprite.setPosition(m_position);

	return true;
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

	m_position.x += (m_direction.x * m_speed.x * deltaMilliseconds);
	m_position.y += (m_direction.y * m_speed.y * deltaMilliseconds);

	m_position.x = std::clamp(m_position.x, 500.f, 1200.f);

	float deltaSeconds = deltaMilliseconds / 1000.f;
	m_fakeDistance += m_fakeSpeed * deltaSeconds;

	distanceInMeters = static_cast<int>(m_fakeDistance);

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
		// World manages this in the end. In retrospective, probably a dumb idea
	}
}

void Zombie::Heal(int amount)
{
	if (currentHealth < maxHealth)
	{
		currentHealth += amount;
	}
}
int Zombie::GetCoins()
{
	return currentCoins;
}
const sf::Vector2f& Zombie::getSpeed() const
{
	return m_speed;
}
void Zombie::setSpeed(const sf::Vector2f& speed)
{
	m_speed = speed;
}

int Zombie::GetHealth()
{
	return currentHealth;
}

void Zombie::render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

