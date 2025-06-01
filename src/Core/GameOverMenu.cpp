#include "Core/GameOverMenu.h"
#include <sstream>

GameOverMenu::GameOverMenu()
{
    font.loadFromFile("../Data/Fonts/PixelifySans-Bold.ttf");
    // GAME OVER title
    m_titleText.setFont(font);
    m_titleText.setCharacterSize(90);
    m_titleText.setFillColor(sf::Color::Red);
    m_titleText.setString("GAME OVER");
    sf::FloatRect titleBounds = m_titleText.getLocalBounds();
    m_titleText.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
    m_titleText.setPosition(WINDOW_WIDTH / 2.f, 100.f);

    // Distance
    m_distanceText.setFont(font);
    m_distanceText.setCharacterSize(40);
    m_distanceText.setFillColor(sf::Color::White);

    // Coins
    m_coinsText.setFont(font);
    m_coinsText.setCharacterSize(40);
    m_coinsText.setFillColor(sf::Color::White);

    // Score
    m_scoreText.setFont(font);
    m_scoreText.setCharacterSize(40);
    m_scoreText.setFillColor(sf::Color::Yellow);

    // Continue instructions
    m_continueText.setFont(font);
    m_continueText.setCharacterSize(40);
    m_continueText.setFillColor(sf::Color::Green);
    m_continueText.setString("Pulsa [Espacio] para volver al menú");
    sf::FloatRect continueBounds = m_continueText.getLocalBounds();
    m_continueText.setOrigin(continueBounds.width / 2.f, continueBounds.height / 2.f);
    m_continueText.setPosition(WINDOW_WIDTH / 2.f, 500.f);
}

void GameOverMenu::setResults(float distance, int coins)
{
    int score = static_cast<int>(distance) * coins;

    m_distanceText.setString("Distancia: " + std::to_string(static_cast<int>(distance)) + " m");
    sf::FloatRect distBounds = m_distanceText.getLocalBounds();
    m_distanceText.setOrigin(distBounds.width / 2.f, distBounds.height / 2.f);
    m_distanceText.setPosition(WINDOW_WIDTH / 2.f, 200.f);

    m_coinsText.setString("Monedas: " + std::to_string(coins));
    sf::FloatRect coinsBounds = m_coinsText.getLocalBounds();
    m_coinsText.setOrigin(coinsBounds.width / 2.f, coinsBounds.height / 2.f);
    m_coinsText.setPosition(WINDOW_WIDTH / 2.f, 250.f);

    m_scoreText.setString("Puntuación: " + std::to_string(score));
    sf::FloatRect scoreBounds = m_scoreText.getLocalBounds();
    m_scoreText.setOrigin(scoreBounds.width / 2.f, scoreBounds.height / 2.f);
    m_scoreText.setPosition(WINDOW_WIDTH / 2.f, 300.f);
}

void GameOverMenu::update(float)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        m_finished = true;
    }
}

void GameOverMenu::render(sf::RenderWindow& window) const
{
    window.draw(m_titleText);
    window.draw(m_distanceText);
    window.draw(m_coinsText);
    window.draw(m_scoreText);
    window.draw(m_continueText);
}

bool GameOverMenu::isFinished() const
{
    return m_finished;
}
void GameOverMenu::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        // Salir con cualquier tecla, o puedes limitar a Enter/Escape/etc.
        m_finished = true;
    }
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        // También puedes permitir clic si quieres
        m_finished = true;
    }
}