#include <cassert>
#include <Core/Game.h>
#include <Core/World.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <Core/AssetManager.h>
void Game::createWorld()
{
	if (m_world)
		delete m_world;

	m_world = new World(*m_window, [this]() {
		m_currentState = State::GameOver;
		}, m_isHardMode);

	m_world->load();
	m_currentState = State::Playing;
}

bool Game::init(GameCreateInfo& createInfo)
{
	m_window = new sf::RenderWindow(
		sf::VideoMode(createInfo.screenWidth, createInfo.screenHeight),
		createInfo.gameTitle
	);

	m_window->setFramerateLimit(createInfo.frameRateLimit);
	changeToMenu();

	return true;
}

Game::~Game()
{
	delete m_world;
	delete m_window;
	delete m_mainMenu;
	delete m_gameOverMenu;
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

		if (m_currentState == State::Menu && m_mainMenu)
			m_mainMenu->handleEvent(event);

		else if (m_currentState == State::Playing && m_world)
			m_world->handleEvent(event);

		else if (m_currentState == State::GameOver && m_gameOverMenu)
			m_gameOverMenu->handleEvent(event);
	}

	if (m_currentState == State::Menu && m_mainMenu)
		m_mainMenu->update(deltaMilliseconds);

	else if (m_currentState == State::Playing && m_world)
		m_world->update(deltaMilliseconds);

	else if (m_currentState == State::GameOver && m_gameOverMenu)
	{
		m_gameOverMenu->update(deltaMilliseconds / 1000.f);

		if (m_gameOverMenu->isFinished())
		{
			delete m_gameOverMenu;
			m_gameOverMenu = nullptr;
			changeToMenu();
		}
	}
	if (m_currentState == State::GameOver && m_world)
	{
		m_lastDistance = m_world->m_lastDistance;
		m_lastMoney = m_world->m_lastMoney;

		delete m_world;
		m_world = nullptr;

		m_gameOverMenu = new GameOverMenu();
		m_gameOverMenu->setResults(m_lastDistance, m_lastMoney);
	}
}


void Game::render()
{
	m_window->clear();

	if (m_currentState == State::Menu && m_mainMenu)
		m_mainMenu->render(*m_window);
	else if (m_currentState == State::Playing && m_world)
		m_world->render(*m_window);
	else if (m_currentState == State::GameOver && m_gameOverMenu)
		m_gameOverMenu->render(*m_window);

	m_window->display();
}

void Game::onPlayPressed(bool isHardMode)
{
	m_isHardMode = isHardMode;
	createWorld();
}

void Game::changeToMenu()
{
	if (m_world)
	{
		delete m_world;
		m_world = nullptr;
	}

	if (m_gameOverMenu)
	{
		delete m_gameOverMenu;
		m_gameOverMenu = nullptr;
	}

	m_mainMenu = new MainMenu(*m_window, [this](bool isHard) { onPlayPressed(isHard); });
	m_currentState = State::Menu;
}

void Game::changeToWorld()
{
	if (m_mainMenu)
	{
		delete m_mainMenu;
		m_mainMenu = nullptr;
	}

	if (m_gameOverMenu)
	{
		delete m_gameOverMenu;
		m_gameOverMenu = nullptr;
	}

	createWorld();
}