#include <Core/MainMenu.h>
#include <iostream>

MainMenu::MainMenu(sf::RenderWindow& window, std::function<void()> onPlayCallback)
    : m_window(window), m_onPlay(onPlayCallback)
{
    setupUI();
}

void MainMenu::setupUI()
{
    m_font.loadFromFile("../Data/Fonts/PixelifySans-Bold.ttf");

    m_titleText.setFont(m_font);
    m_titleText.setString("RIFF&RUN");
    m_titleText.setCharacterSize(60);
    m_titleText.setFillColor(sf::Color::White);
    m_titleText.setPosition(200.f, 100.f);

    m_playButton.setFont(m_font);
    m_playButton.setString("JUGAR");
    m_playButton.setCharacterSize(40);
    m_playButton.setFillColor(sf::Color::Green);
    m_playButton.setPosition(280.f, 300.f);
}

void MainMenu::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

        if (m_playButton.getGlobalBounds().contains(mousePos))
        {
            m_onPlay(); // Cambia al mundo
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
    m_window.draw(m_playButton);
}