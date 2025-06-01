#include "Gameplay/Obstacle.h"

Obstacle::Obstacle(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture, float gravity)
    : m_velocity(0.f, 0.f),
     m_gravity(gravity)
{
    float randomBoost = static_cast<float>(std::rand() % 200);

    m_gravity += randomBoost;

    m_sprite.setTexture(*texture);
    m_sprite.setPosition(position);
    // Escala el sprite si quieres que encaje en el tamaño deseado
    const auto texSize = texture->getSize();
    m_sprite.setScale(size.x / texSize.x, size.y / texSize.y);

}

void Obstacle::update(float deltaSeconds)
{
    m_velocity.y += m_gravity * deltaSeconds; // apply gravity
    m_sprite.move(0.f, m_velocity.y * deltaSeconds);
}

void Obstacle::render(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}

const sf::FloatRect Obstacle::getBounds() const
{
    return m_sprite.getGlobalBounds();
}