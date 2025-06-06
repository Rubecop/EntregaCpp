#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
class Coin
{
public:
    Coin(const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture);

    void update(float deltaSeconds);
    void render(sf::RenderWindow& window) const;

    const sf::FloatRect getBounds() const;
private:
    float m_gravity;

    sf::RectangleShape m_shape;
    sf::Vector2f m_velocity;
    sf::Sprite m_sprite;
};