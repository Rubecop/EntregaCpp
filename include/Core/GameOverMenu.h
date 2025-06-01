#pragma once
#include <SFML/Graphics.hpp>

class GameOverMenu
{
public:
    GameOverMenu();

    void setResults(float distance, int coins);
    void update(float deltaSeconds); // opcional, para animaciones
    void render(sf::RenderWindow& window) const;
    void handleEvent(const sf::Event& event);
    bool isFinished() const; // true si el usuario quiere volver al menú

private:
    sf::Font font;
    sf::Text m_titleText;
    sf::Text m_distanceText;
    sf::Text m_coinsText;
    sf::Text m_scoreText;
    sf::Text m_continueText;

    float WINDOW_WIDTH = 1920.f;
    float WINDOW_HEIGHT = 1080.f;


    bool m_finished = false;
};