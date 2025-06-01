#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class MainMenu
{
public:
    MainMenu(sf::RenderWindow& window, std::function<void()> onPlayCallback);

    void handleEvent(const sf::Event& event);
    void update(float dt);
    void render(sf::RenderWindow& window);

private:
    sf::RenderWindow& m_window;
    sf::Font m_font;
    sf::Text m_titleText;
    sf::Text m_playButton;

    std::function<void()> m_onPlay;

    void setupUI();
};