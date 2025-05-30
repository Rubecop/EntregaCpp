#pragma once
#include <SFML/Graphics.hpp>

class Obstacle
{
public:
    Obstacle(const sf::Vector2f& position, const sf::Vector2f& size);

    void update(float deltaSeconds);
    void render(sf::RenderWindow& window) const;
    const sf::FloatRect getBounds() const;

private:
    sf::RectangleShape m_shape;
    sf::Vector2f m_velocity;
    float m_gravity; // acceleration per second
};