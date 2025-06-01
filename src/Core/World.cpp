#include <Core/AssetManager.h>
#include <Core/World.h>
#include <Gameplay/Zombie.h>
#include <Render/SFMLOrthogonalLayer.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <tmxlite/Map.hpp>

World::~World()
{
	delete m_player;
	delete m_spawnerManager;
	delete m_manualMap;
	delete m_uiManager;
	delete m_coinSpawner;
	delete m_powerUpSpawner;
}

World::World(sf::RenderWindow& window, std::function<void()> onDeathCallback, bool isHardMode)
	: m_onDeathCallback(onDeathCallback),
	m_isHardMode(isHardMode)
{
	constexpr float millisecondsToSeconds = 1 / 1000.f;

	m_manualMap = new ManualMap();

	Zombie* zombie = new Zombie();
	zombie->init();
	m_player = zombie;

	if (!m_player) {
		std::cout << "el player no se inicia";
	} else{ std::cout << "player spawneado"; }

	m_uiManager = new UIManager(m_player);
	zombie->setPosition({ 850.0f, 750.0f });
	sf::FloatRect playerBounds = m_player->getBounds();

	float spawnRate = 0.f;
	if (m_isHardMode) 
	{
		 spawnRate = 1.f;
	}
	else
	{
		spawnRate = 2.f;
	}

	m_spawnerManager = new SpawnerManager(m_player, spawnRate, { 200.f, 300.f }, 2.0f, m_isHardMode);
	m_coinSpawner = new CoinSpawner(m_player,7.0f,550.f,1150.f,sf::Vector2f(0.f, 0.f),sf::Vector2f(100.f, 100.f));
	m_powerUpSpawner = new PowerUpSpawner(m_player, 10.0f, 550.f, 1150.f, sf::Vector2f(0.f, 0.f), sf::Vector2f(100.f, 100.f));

	if (m_spawnerManager)
	{
		m_spawnerManager->handlePlayerCollision(playerBounds);
	}
}

bool World::load()
{
	
	return true;
}

void World::update(uint32_t deltaMilliseconds)
{
	m_player->update(deltaMilliseconds);

	float deltaSeconds = deltaMilliseconds / 1000.f;
	if (m_spawnerManager)
		m_spawnerManager->update(deltaSeconds);

	m_coinSpawner->update(deltaSeconds);
	m_powerUpSpawner->update(deltaSeconds);
	m_manualMap->update(deltaSeconds);
	m_uiManager->updateDistance(deltaMilliseconds);

	if (m_player && m_spawnerManager)
	{
		sf::FloatRect playerBounds = m_player->getBounds();
		m_spawnerManager->handlePlayerCollision(playerBounds);
	}

	if (m_player && m_coinSpawner)
	{
		sf::FloatRect playerBounds = m_player->getBounds();
		m_coinSpawner->handlePlayerCollision(playerBounds);
	}
	if (m_player && m_powerUpSpawner)
	{
		sf::FloatRect playerBounds = m_player->getBounds();
		m_powerUpSpawner->handlePlayerCollision(playerBounds);
	}
	checkPlayerDeath();
}


void World::render(sf::RenderWindow& window)
{
	if (m_manualMap)
		m_manualMap->render(window);

	if (m_spawnerManager)
		m_spawnerManager->render(window);

	if (m_uiManager)
		m_uiManager->render(window);

	m_player->render(window);
	m_coinSpawner->render(window);
	m_powerUpSpawner->render(window);
}

void World::handleEvent(const sf::Event& event)
{
}

void World::checkPlayerDeath()
{
	if (m_player && m_player->GetHealth() <= 0 && !m_isGameOver)
	{
		m_isGameOver = true;
		m_lastDistance = m_player->distanceInMeters;
		m_lastMoney = m_player->GetCoins();

		if (m_onDeathCallback)
			m_onDeathCallback();
	}
}
bool World::isGameOver() const
{
	return m_isGameOver;
}