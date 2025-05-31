#include <Core/AssetManager.h>
#include <Core/World.h>
#include <Gameplay/Zombie.h>
#include <Render/SFMLOrthogonalLayer.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <tmxlite/Map.hpp>

World::~World()
{
	delete m_enemy;
	delete m_layerZero;
	delete m_layerOne;
	delete m_layerTwo;
	delete m_map;
	delete m_spawnerManager;
	delete m_manualMap;
}


bool World::load()
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
	m_enemy = zombie;
	zombie->setPosition({ 850.0f, 750.0f });
	sf::FloatRect playerBounds = m_enemy->getBounds();

	m_spawnerManager = new SpawnerManager(2.0f, { 200.f, 300.f }, 4.0f);

	if (m_spawnerManager)
	{
		// Asumamos que SpawnerManager expone sus spawners internamente; 
		// para no romper encapsulación, le añadiremos un método en SpawnerManager:
		m_spawnerManager->handlePlayerCollision(playerBounds);
	}
	return initOk;
}

void World::update(uint32_t deltaMilliseconds)
{
	// Update actors
	m_enemy->update(deltaMilliseconds);

	float deltaSeconds = deltaMilliseconds / 1000.f;
	if (m_spawnerManager)
		m_spawnerManager->update(deltaSeconds);

	if (m_enemy && m_spawnerManager)
	{
		sf::FloatRect playerBounds = m_enemy->getBounds();
		m_spawnerManager->handlePlayerCollision(playerBounds);
	}
}

void World::render(sf::RenderWindow& window)
{
	if (m_manualMap)
		m_manualMap->render(window);

	m_enemy->render(window);
	if (m_spawnerManager)
		m_spawnerManager->render(window);
}