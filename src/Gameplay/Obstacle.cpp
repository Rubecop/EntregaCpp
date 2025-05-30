#include "Gameplay/Obstacle.h"

Obstacle::Obstacle(const sf::Vector2f& position, const sf::Vector2f& size)
    : m_velocity(0.f, 0.f), m_gravity(500.f) // pixels/sec²
{
    m_shape.setSize(size);
    m_shape.setFillColor(sf::Color::Blue);
    m_shape.setPosition(position);
}

void Obstacle::update(float deltaSeconds)
{
    m_velocity.y += m_gravity * deltaSeconds; // apply gravity
    m_shape.move(0.f, m_velocity.y * deltaSeconds); // move obstacle
}

void Obstacle::render(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}

const sf::FloatRect Obstacle::getBounds() const
{
    return m_shape.getGlobalBounds();
}