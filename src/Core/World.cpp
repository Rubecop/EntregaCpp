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
	delete m_obstacleSpawner;
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
	m_obstacle = new Obstacle({ 400.f, 0.f }, { 50.f, 50.f });

	m_enemy = zombie;
	zombie->setPosition({ 850.0f, 750.0f });
	
	m_obstacleSpawner = new ObstacleSpawner(
		2.0f,                // Intervalo de spawn: cada 2 segundos
		{ 600.f, 600.f },    // Área de spawn (ancho del juego)
		{ 250.f, 250.f }       // Tamaño del obstáculo
	);

	// To-Do, Load level: this should have its own class
	m_map = new tmx::Map();
	m_map->load("../Data/Levels/demo.tmx");
	m_layerZero = new MapLayer(*m_map, 0);
	m_layerOne = new MapLayer(*m_map, 1);
	m_layerTwo = new MapLayer(*m_map, 2);

	m_collisionLayer = new ObjectLayer(*m_map, 3);

	return initOk;
}

void World::update(uint32_t deltaMilliseconds)
{
	// To-Do: update level
	m_layerZero->update(sf::milliseconds(deltaMilliseconds));

	// Update actors
	m_enemy->update(deltaMilliseconds);
	if (m_obstacle)
	{
		m_obstacle->update(deltaMilliseconds / 1000.f); // convierte ms a segundos
	}
	if (m_obstacleSpawner)
	{
		m_obstacleSpawner->update(deltaMilliseconds / 1000.f);
	}
	// Check for collisions (We could do it in a function here or have a collision manager if it gets complex)
	const auto& collisionShapes = m_collisionLayer->getShapes();
	for (const auto* shape : collisionShapes)
	{
		if (shape->getGlobalBounds().intersects(m_enemy->getBounds()))
		{
#if DEBUG_MODE
			printf("Collision is detected");
#endif
		}
	}
}

void World::render(sf::RenderWindow& window)
{
	window.draw(*m_layerZero);
	window.draw(*m_layerOne);
	window.draw(*m_layerTwo);
	window.draw(*m_collisionLayer);
	m_enemy->render(window);
	if (m_obstacle)
	{
		m_obstacle->render(window);
	}
	if (m_obstacleSpawner)
	{
		m_obstacleSpawner->render(window);
	}
}