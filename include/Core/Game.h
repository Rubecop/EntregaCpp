#pragma once

#include <cstdint>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include <Core/MainMenu.h>
#include <Core/World.h>
#include <Core/GameOverMenu.h>

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
		bool m_isHardMode{ false };

		void update(uint32_t deltaMilliseconds);
		void render();
		void onPlayPressed(bool isHardMode);
		void createWorld();

		float m_lastDistance = 0.f;
		int m_lastMoney = 0;

	private:

		enum class State
		{
			Menu,
			Playing,
			GameOver
		};
		void changeToMenu();
		void changeToWorld();

		State m_currentState{ State::Menu };
		World* m_world{ nullptr };
		MainMenu* m_mainMenu{ nullptr };
		GameOverMenu* m_gameOverMenu = { nullptr };

		sf::RenderWindow* m_window{ nullptr };
};