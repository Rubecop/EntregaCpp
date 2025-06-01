#include <Gameplay/PowerUpBase.h>

PowerUpBase::PowerUpBase(Zombie* player, const sf::Vector2f& position, const std::string& texturePath)
    : m_player(player)
{
    m_texture.loadFromFile(texturePath);
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(position);
}

void PowerUpBase::update(float deltaTime)
{
    if (m_collected || !m_player){ return; }
    m_sprite.move(0.f, m_fallSpeed * deltaTime);

    if (m_sprite.getGlobalBounds().intersects(m_player->getBounds()))
    {
        m_collected = true;
        onGrab();
    }
}

void PowerUpBase::render(sf::RenderWindow& window)
{
    if (!m_collected)
        window.draw(m_sprite);
}

bool PowerUpBase::isMarkedForRemoval() const
{
    return m_collected;
}
const sf::FloatRect PowerUpBase::getBounds() const
{
    return m_sprite.getGlobalBounds();
}