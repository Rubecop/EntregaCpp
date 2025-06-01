#pragma once

#include <Gameplay/GameObject.h>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>


class Enemy : public GameObject
{
	public:
		struct EnemyDescriptor
		{
			sf::Vector2f position;
			sf::Texture* texture{ nullptr };
			float tileWidth{ .0f };
			float tileHeight{ .0f };
		};

		~Enemy() override = default;
		bool init(const EnemyDescriptor& enemyDescriptor);

		void update(float deltaMilliseconds) override;
		void render(sf::RenderWindow& window) override;

		sf::FloatRect getBounds() const { return m_sprite.getGlobalBounds(); }
	protected:

		float m_tileWidth{ .0f };
		float m_tileHeight{ .0f };

		sf::Sprite m_sprite;
};