#pragma once

#include <cstdint>
#include "Gameplay/Obstacle.h"
#include <Gameplay/ObstacleSpawner.h>
#include <Gameplay/SpawnerManager.h>
#include <Gameplay/CoinSpawner.h>
#include <Gameplay/AddHealthPowerUp.h>
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

		// TO-DO: Ideally the scene should be read from file.
		bool load();

		// To-Do: Implement a unload()

		void update(uint32_t deltaMilliseconds);
		void render(sf::RenderWindow& window);
		void handleEvent(const sf::Event& event);
		bool isGameOver() const;

	private:

		// This is just an example. Think a good way to group the actors of your game. If they need any type of manager, etc...
		Zombie* m_player{ nullptr };

		AddHealthPowerUp* m_healthPowerup{ nullptr };

		ManualMap* m_manualMap = nullptr;

		UIManager* m_uiManager = nullptr;

		ObjectLayer* m_collisionLayer{ nullptr };

		//ObstacleTest
		Obstacle* m_obstacle = nullptr;

		ObstacleSpawner* m_obstacleSpawner = nullptr;
		SpawnerManager* m_spawnerManager = nullptr;
		CoinSpawner* m_coinSpawner = nullptr;

		std::function<void()> m_onDeathCallback;
		bool m_isGameOver{ false };
		bool m_isHardMode{ false };
		void checkPlayerDeath();
};