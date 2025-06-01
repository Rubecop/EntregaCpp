#pragma once

#include <Gameplay/Enemy.h>


class Zombie : public Enemy
{
	public:

		struct ZombieDescriptor : EnemyDescriptor
		{
			sf::Vector2f speed{ .0f, .0f };
		};

		bool init(const ZombieDescriptor& enemyDescriptor);

		void update(float deltaMilliseconds) override;

		void TakeDamage(int health);
		void Heal(int health);

		void AddCoins(int amount);

		int GetHealth();
		int GetCoins();

		int currentHealth = 0;
		int currentCoins = 0;
	private:

		int maxHealth = 0;
		sf::Vector2f m_direction{ .0f, .0f };
		sf::Vector2f m_speed{ .0f, .0f };
};