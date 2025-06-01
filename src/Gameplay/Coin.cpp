#include "Gameplay/Coin.h"

Coin::Coin(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture)
    : m_velocity(0.f, 0.f), m_gravity(400.f)
{
    m_sprite.setTexture(*texture);
    m_sprite.setPosition(position);
    const auto texSize = texture->getSize();
    m_sprite.setScale(size.x / texSize.x, size.y / texSize.y);
}

void Coin::update(float deltaSeconds)
{
    m_velocity.y += m_gravity * deltaSeconds;
    m_sprite.move(0.f, m_velocity.y * deltaSeconds);
}

void Coin::render(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}

const sf::FloatRect Coin::getBounds() const
{
    return m_sprite.getGlobalBounds();
}