#pragma once

#include <cstdint>
#include "Gameplay/Obstacle.h"
#include <Gameplay/ObstacleSpawner.h>
#include <Gameplay/SpawnerManager.h>
#include <Gameplay/CoinSpawner.h>
#include <Gameplay/PowerUpSpawner.h>
#include <Gameplay/Zombie.h>

#include "Render/ManualMap.h"
#include <UI/UIManager.h>
#include <functional>

namespace sf
{
	class RenderWindow;
}

namespace tmx
{
	class Map;
}

class MapLayer;
class ObjectLayer;

class World
{
	public:
		World(sf::RenderWindow& window, std::function<void()> onDeathCallback, bool isHardMode);
		~World();

		bool load();
		void update(uint32_t deltaMilliseconds);
		void render(sf::RenderWindow& window);
		void handleEvent(const sf::Event& event);
		bool isGameOver() const;

		float m_lastDistance = 0.f;
		int m_lastMoney = 0;

	private:
		Zombie* m_player{ nullptr };

		PowerUpSpawner* m_powerUpSpawner{ nullptr };

		ManualMap* m_manualMap = nullptr;

		UIManager* m_uiManager = nullptr;

		ObjectLayer* m_collisionLayer{ nullptr };

		ObstacleSpawner* m_obstacleSpawner = nullptr;
		SpawnerManager* m_spawnerManager = nullptr;
		CoinSpawner* m_coinSpawner = nullptr;

		std::function<void()> m_onDeathCallback;
		bool m_isGameOver{ false };
		bool m_isHardMode{ false };
		void checkPlayerDeath();
};