#include <UI/UIManager.h>
#include <iostream>
#include <Core/AssetManager.h>

UIManager::UIManager(Zombie* player)
    : m_player(player)
{
    if (!font.loadFromFile("../Data/Fonts/PixelifySans-Bold.ttf")) {
        std::cerr << "Error cargando la fuente\n";
    }
    coinText.setFont(font);
    coinText.setCharacterSize(60);
    coinText.setFillColor(sf::Color::Black);
    coinText.setPosition(1690.f,5.f);

    m_heartTexture = AssetManager::getInstance()->loadTexture("../Data/Images/UI/HealthUI.png");
    m_coinTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Grabbables/coin.png");

    m_coinSprite.setScale(0.25f, 0.25f);
    m_coinSprite.setTexture(*m_coinTexture);
    m_coinSprite.setPosition(1600.f, 0.f);

    m_distanceText.setFont(font);
    m_distanceText.setCharacterSize(32);
    m_distanceText.setFillColor(sf::Color::White);
    m_distanceText.setPosition(850.f,0.f);
    m_distanceText.setString("Distancia: 0 m");

    for (int i = 0; i < 3; ++i)
    {
        sf::Sprite heart;
        heart.setTexture(*m_heartTexture);
        heart.setPosition(10.f + i * 120.f, 10.f);
        m_heartSprites.push_back(heart);
    }
}

void UIManager::render(sf::RenderWindow& window)
{
    if (!m_player)
        return;

    int lifeCount = m_player->GetHealth();
    //std::cout << "Debug: player health = " << m_player->GetHealth() << std::endl;
    //std::cout << "Debug: player coins = " << m_player->GetCoins() << std::endl;

    coinText.setString("" + std::to_string(m_player->GetCoins()));

    for (int i = 0; i < lifeCount && i < 3; ++i)
    {
        window.draw(m_heartSprites[i]);
    }
    window.draw(m_coinSprite);
    window.draw(coinText);
    window.draw(m_distanceText);
}

void UIManager::updateDistance(float deltaMilliseconds)
{
    m_distanceText.setString("Distancia: " + std::to_string(m_player->distanciaMetros) + " m");
}
