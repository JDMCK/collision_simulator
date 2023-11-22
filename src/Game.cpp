#include "Game.h"

void Game::run()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Geometry Wars" };
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}

void Game::init(const std::string & config)
{

}

void Game::setPaused(bool paused)
{

}


void Game::sMovement()
{

}

void Game::sUserInput()
{

}

void Game::sLifespan()
{

}

void Game::sRender()
{

}

void Game::sEnemySpawner()
{

}

void Game::sCollision()
{

}

void Game::spawnPlayer()
{
    // auto p = m_entities.addEntity(PLAYER);
    // p -> cTransform = std::make_shared<CTransform>();
    // p -> cShape = std::make_shared<CShape>();
}

void Game::spawnEnemy()
{

}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{

}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & mousePos)
{

}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{

}