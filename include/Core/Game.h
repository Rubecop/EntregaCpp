#pragma once

#include <cstdint>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include <Core/MainMenu.h>
#include <Core/World.h>

namespace sf
{
	class RenderWindow;
}

class World;

class Game
{
	public:

		struct GameCreateInfo
		{
			std::string gameTitle;
			uint32_t screenWidth;
			uint32_t screenHeight;
			uint32_t frameRateLimit;
		};

		~Game();

		bool init(GameCreateInfo& createInfo);

		bool isRunning() const;

		void update(uint32_t deltaMilliseconds);
		void render();

	private:

		enum class State
		{
			Menu,
			Playing
		};
		State m_currentState{ State::Menu };
		sf::RenderWindow* m_window{ nullptr };
		World* m_world{ nullptr };
		MainMenu* m_mainMenu{ nullptr };

		void changeToMenu();
		void changeToWorld();
};