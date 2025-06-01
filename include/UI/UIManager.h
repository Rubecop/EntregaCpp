#pragma once
#include <SFML/Graphics.hpp>
#include <Gameplay/Zombie.h>

class UIManager
{
public:
    UIManager(Zombie* player);
    void render(sf::RenderWindow& window);
    void updateDistance(float deltaMilliseconds);
private:
    Zombie* m_player;

    sf::Texture* m_heartTexture;
    std::vector<sf::Sprite> m_heartSprites;
    sf::Texture* m_coinTexture;
    sf::Sprite m_coinSprite;
    sf::Font font;
    sf::Text coinText;
    sf::Text m_distanceText;
};