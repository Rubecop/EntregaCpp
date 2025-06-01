// PowerUp.h
#pragma once
#include <SFML/Graphics.hpp>
#include <Utils/IGrabbable.h>
#include <Gameplay/Zombie.h>

class PowerUpBase : public IGrabbable
{
public:
    PowerUpBase(Zombie* player, const sf::Vector2f& position, const std::string& texturePath);
    virtual ~PowerUpBase() = default;

    virtual void onGrab() override = 0;

    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    bool isMarkedForRemoval() const;

protected:
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    Zombie* m_player = nullptr;
    bool m_collected = false;
    float m_fallSpeed = 100.f; // Velocidad de caída (px por segundo)
};