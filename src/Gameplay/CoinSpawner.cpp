#include "Gameplay/CoinSpawner.h"
#include <Core/AssetManager.h>
#include <cstdlib> // for rand()
#include <ctime>   // for time()

CoinSpawner::CoinSpawner(Zombie* player,
    float spawnInterval,
    float minX,
    float maxX,
    const sf::Vector2f& spawnPosition,
    const sf::Vector2f& coinSize,
    float initialOffset)
    : m_spawnInterval(spawnInterval)
    , m_elapsedTime(initialOffset)
    , m_enabled(true)
    , m_minX(minX)
    , m_maxX(maxX)
    , m_spawnPosition(spawnPosition)
    , m_coinSize(coinSize)
    , m_player(player)
{

}

CoinSpawner::~CoinSpawner()
{
    for (auto* coin : m_coins)
        delete coin;
    m_coins.clear();
}

void CoinSpawner::update(float deltaSeconds)
{
    // Actualiza monedas existentes
    for (int i = static_cast<int>(m_coins.size()) - 1; i >= 0; --i)
    {
        Coin* coin = m_coins[i];
        coin->update(deltaSeconds);

        if (coin->getBounds().top > 1200)
        {
            delete coin;
            m_coins.erase(m_coins.begin() + i);
        }
    }

    if (!m_enabled)
        return;

    // Control del spawn de monedas en lote (3 monedas)
    m_elapsedTime += deltaSeconds;
    if (m_elapsedTime >= m_spawnInterval)
    {
        m_elapsedTime = 0.f;
        m_coinsSpawnedInBatch = 0;
        m_singleElapsedTime = 0.f;

        // Elegimos una posición aleatoria para el batch (puede ser fija si quieres)
        float xPos = m_minX + static_cast<float>(rand()) / RAND_MAX * (m_maxX - m_minX);
        m_currentBatchSpawnPos = sf::Vector2f(xPos,-250);
    }

    if (m_coinsSpawnedInBatch < 3)
    {
        m_singleElapsedTime += deltaSeconds;
        if (m_singleElapsedTime >= m_singleSpawnInterval)
        {
            spawnSingleCoin(m_coinsSpawnedInBatch);
            m_coinsSpawnedInBatch++;
            m_singleElapsedTime = 0.f;
        }
    }
    //for (int i = static_cast<int>(m_coins.size()) - 1; i >= 0; --i)
    //{
    //    Coin* coin = m_coins[i];
    //    coin->update(deltaSeconds);

    //    // Si la moneda cae por debajo de la ventana (ejemplo: > 800 en y)
    //    if (coin->getBounds().top > 800)
    //    {
    //        delete coin;
    //        m_coins.erase(m_coins.begin() + i);
    //    }
    //}

    //if (!m_enabled)
    //    return;

    //m_elapsedTime += deltaSeconds;

    //if (m_elapsedTime >= m_spawnInterval)
    //{
    //    spawnCoins();
    //    m_elapsedTime -= m_spawnInterval;
    //}
}

void CoinSpawner::render(sf::RenderWindow& window)
{
    for (auto* coin : m_coins)
    {
        coin->render(window);
    }
}

void CoinSpawner::spawnCoins()
{
    sf::Texture* coinTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Grabbables/coin.png");

    for (int i = 0; i < 3; ++i)
    {
        Coin* newCoin = new Coin(m_spawnPosition, m_coinSize, coinTexture);
        m_coins.push_back(newCoin);
    }
}

void CoinSpawner::spawnSingleCoin(int index)
{
    sf::Texture* coinTexture = AssetManager::getInstance()->loadTexture("../Data/Images/Grabbables/coin.png");
    sf::Vector2f pos = m_currentBatchSpawnPos;
    // Usamos la misma posición para todas las monedas del batch

    Coin* newCoin = new Coin(pos, m_coinSize, coinTexture);
    m_coins.push_back(newCoin);
}

void CoinSpawner::handlePlayerCollision(const sf::FloatRect& playerBounds)
{
    for (int i = static_cast<int>(m_coins.size()) - 1; i >= 0; --i)
    {
        Coin* coin = m_coins[i];
        if (coin->getBounds().intersects(playerBounds))
        {
            m_player->AddCoins(1);
            delete coin;
            m_coins.erase(m_coins.begin() + i);
        }
    }
}

void CoinSpawner::resetTimer()
{
    m_elapsedTime = 0.f;
}