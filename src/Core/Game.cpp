#include <cassert>
#include <Core/Game.h>
#include <Core/World.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

bool Game::init(GameCreateInfo& createInfo)
{
	m_window = new sf::RenderWindow(
		sf::VideoMode(createInfo.screenWidth, createInfo.screenHeight),
		createInfo.gameTitle
	);
	m_window->setFramerateLimit(createInfo.frameRateLimit);

	changeToMenu(); // Empezamos en el menú

	return true;
	/*assert(m_window == nullptr && m_world == nullptr && "Game is already initialized, we are about to leak memory");

	m_window = new sf::RenderWindow({ createInfo.screenWidth, createInfo.screenHeight }, createInfo.gameTitle);
	m_window->setFramerateLimit(createInfo.frameRateLimit);

	changeToMenu();

	m_world = new World();
	const bool loadOk = m_world->load();
	return loadOk;*/
}

Game::~Game()
{
	// To-Do: make sure m_world is unloaded()

	delete m_world;
	delete m_window;
	delete m_mainMenu;
}

bool Game::isRunning() const 
{ 
	return m_window->isOpen(); 
}

void Game::update(uint32_t deltaMilliseconds)
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window->close();

		// Input a cada estado
		if (m_currentState == State::Menu && m_mainMenu)
			m_mainMenu->handleEvent(event);
		else if (m_currentState == State::Playing && m_world)
			m_world->handleEvent(event);
	}

	if (m_currentState == State::Menu && m_mainMenu)
		m_mainMenu->update(deltaMilliseconds);
	else if (m_currentState == State::Playing && m_world)
		m_world->update(deltaMilliseconds);

	// Si quieres volver al menú cuando mueres
	if (m_currentState == State::Playing && m_world && m_world->isGameOver())
		changeToMenu();


	//// Check if user closed the window
	//for (auto event = sf::Event(); m_window->pollEvent(event);)
	//{
	//	if (event.type == sf::Event::Closed)
	//	{
	//		m_window->close();
	//	}
	//}

	//// Update scene here
	//m_world->update(deltaMilliseconds);
}

void Game::render()
{
	m_window->clear();

	if (m_currentState == State::Menu && m_mainMenu)
		m_mainMenu->render(*m_window);

	else if (m_currentState == State::Playing && m_world)
		m_world->render(*m_window);

	m_window->display();
}

void Game::changeToMenu()
{
	// Borramos el mundo si existe
	if (m_world)
	{
		delete m_world;
		m_world = nullptr;
	}

	// Creamos el menú
	m_mainMenu = new MainMenu(*m_window, [this]() {
		changeToWorld(); // iniciar el juego al pulsar "Play"
		});

	m_currentState = State::Menu;
}

void Game::changeToWorld()
{
	if (m_mainMenu)
	{
		delete m_mainMenu;
		m_mainMenu = nullptr;
	}

	// Borramos el mundo anterior si existe
	if (m_world)
	{
		delete m_world;
		m_world = nullptr;
	}

	// Creamos el nuevo mundo con el callback de muerte
	m_world = new World(*m_window, [this]() {
		changeToMenu(); // volver al menú al morir
		});

	m_world->load(); // No olvides cargar el mundo

	m_currentState = State::Playing;
}
