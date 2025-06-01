#include <Core/MainMenu.h>
#include <iostream>

MainMenu::MainMenu(sf::RenderWindow& window, std::function<void(bool)> onPlayCallback)
    : m_window(window), m_onPlay(onPlayCallback)
{
    setupUI();
}

void MainMenu::setupUI()
{
    m_font.loadFromFile("../Data/Fonts/PixelifySans-Bold.ttf");

    m_titleText.setFont(m_font);
    m_titleText.setString("RIFF&RUN");
    m_titleText.setCharacterSize(100);
    m_titleText.setFillColor(sf::Color::White);
    m_titleText.setPosition(700.f, 50.f);

    m_playEasy.setFont(m_font);
    m_playEasy.setString("EASY MODE");
    m_playEasy.setCharacterSize(50);
    m_playEasy.setFillColor(sf::Color::Green);
    m_playEasy.setPosition(800.f, 400.f);

    m_playHard.setFont(m_font);
    m_playHard.setString("HARD MODE");
    m_playHard.setCharacterSize(50);
    m_playHard.setFillColor(sf::Color::Red);
    m_playHard.setPosition(800.f, 600.f);
}

void MainMenu::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

        if (m_playEasy.getGlobalBounds().contains(mousePos))
        {
            m_onPlay(false); // Cambia al mundo
        }

        if (m_playHard.getGlobalBounds().contains(mousePos))
        {
            m_onPlay(true); // Cambia al mundo
        }
    }
}

void MainMenu::update(float dt)
{
    // Animaciones o lógica futura del menú (opcional)
}

void MainMenu::render(sf::RenderWindow& window)
{
    m_window.draw(m_titleText);
    m_window.draw(m_playEasy);
    m_window.draw(m_playHard);
}