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
}

World::World(sf::RenderWindow& window, std::function<void()> onDeathCallback)
	: m_onDeathCallback(onDeathCallback)
{
	constexpr float millisecondsToSeconds = 1 / 1000.f;

	// To-Do, read ALL from file, this is just a quick example to understand that here is where entities are created but consider grouping/managing actors in a smarter way
	sf::Texture* zombieTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Enemies/zombie.png");
	Zombie::ZombieDescriptor zombieDescriptor;
	zombieDescriptor.texture = zombieTexture;
	zombieDescriptor.position = { 50.f, 50.f };
	zombieDescriptor.speed = { 400.f * millisecondsToSeconds, .0f }; // 400 units per second, or 0.4 units per millisecond, using the latter so it's in alignment with delta time
	zombieDescriptor.tileWidth = 192.f;
	zombieDescriptor.tileHeight = 256.f;
	Zombie* zombie = new Zombie();
	const bool initOk = zombie->init(zombieDescriptor);

	m_manualMap = new ManualMap();
	m_player = zombie;

	m_uiManager = new UIManager(m_player);
	zombie->setPosition({ 850.0f, 750.0f });
	sf::FloatRect playerBounds = m_player->getBounds();

	m_spawnerManager = new SpawnerManager(m_player, 2.0f, { 200.f, 300.f }, 4.0f);

	m_healthPowerup = new AddHealthPowerUp(m_player, { 700.f,0.f });

	m_coinSpawner = new CoinSpawner(m_player,
		7.0f,                // cada 5 segundos
		550.f,               // min X
		1150.f,              // max X
		sf::Vector2f(0.f, 0.f),  // posición Y fija (ajusta)
		sf::Vector2f(100.f, 100.f)); // tamaño de la moneda

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
	// Update actors
	m_player->update(deltaMilliseconds);

	float deltaSeconds = deltaMilliseconds / 1000.f;
	if (m_spawnerManager)
		m_spawnerManager->update(deltaSeconds);

	m_coinSpawner->update(deltaSeconds);

	m_manualMap->update(deltaSeconds);

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
	checkPlayerDeath();
}


void World::render(sf::RenderWindow& window)
{
	if (m_manualMap)
		m_manualMap->render(window);

	m_player->render(window);
	if (m_spawnerManager)
		m_spawnerManager->render(window);

	if (m_uiManager)
		m_uiManager->render(window);
	m_coinSpawner->render(window);
}

void World::handleEvent(const sf::Event& event)
{
}

void World::checkPlayerDeath()
{
	if (m_player && m_player->GetHealth() <= 0 && !m_isGameOver)
	{
		m_isGameOver = true;
		if (m_onDeathCallback)
			m_onDeathCallback();
	}
}
bool World::isGameOver() const
{
	return m_isGameOver;
}