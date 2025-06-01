#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class MainMenu
{
public:
    MainMenu(sf::RenderWindow& window, std::function<void(bool)> onPlayCallback);

    void handleEvent(const sf::Event& event);
    void update(float dt);
    void render(sf::RenderWindow& window);

private:
    void setupUI();

    std::function<void(bool)> m_onPlay;

    sf::RenderWindow& m_window;
    sf::Font m_font;
    sf::Text m_titleText;
    sf::Text m_playEasy;
    sf::Text m_playHard;
};