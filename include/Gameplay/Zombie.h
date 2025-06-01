#pragma once

#include <Gameplay/Enemy.h>


class Zombie : public Enemy
{
	public:

		Zombie();

		bool init();
		void update(float deltaMilliseconds) override;
		void render(sf::RenderWindow& window);

		void TakeDamage(int health);
		void Heal(int health);

		void AddCoins(int amount);

		int GetHealth();
		int GetCoins();

		int currentHealth = 0;
		int currentCoins = 0;

		float m_fakeDistance = 0.f;
		float m_fakeSpeed = 50.f;
		int distanciaMetros = 0;

		const sf::Vector2f& getSpeed() const;
		void setSpeed(const sf::Vector2f& speed);


	private:
		sf::Texture* m_texture = nullptr;

		int maxHealth = 3;
		//sf::Vector2f m_position = { 50.f, 50.f };
		sf::Vector2f m_direction{ .0f, .0f };
		sf::Vector2f m_speed = { 0.4f, 0.f };

};