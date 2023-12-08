#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include <algorithm>

Game::Game()
{
    init();
}

void Game::run()
{
    while (m_window.isOpen())
    {
        m_entities.update();
        m_window.clear();
        if (!m_paused)
        {
            sLifespan();
            sPlayerInput();
            sMovement();
            sCollision();
            sParentChild();
        }
        sAnimate();
        sUserInput();
        sRender();
        m_window.display();
    }
}

void Game::init()
{
    m_window.create(sf::VideoMode(1280, 720), "Collision");
    m_window.setFramerateLimit(60);

    m_windowWidth = 1280;
    m_windowHeight = 720;

    spawnPlayer();
    spawnPlatforms();
}

void Game::spawnPlatforms()
{
    auto p1 = m_entities.addEntity(PLATFORM);
    p1->cTransform = std::make_shared<CTransform>(Vec2(m_windowWidth / 2, m_windowHeight - 100));
    p1->cRectCollider = std::make_shared<CRectCollider>(200, 30);
    p1->cRectShape = std::make_shared<CRectShape>(200, 30, sf::Color::Green, sf::Color::White, 0);

    auto p2 = m_entities.addEntity(PLATFORM);
    p2->cTransform = std::make_shared<CTransform>(Vec2(m_windowWidth - 200, m_windowHeight - 100));
    p2->cRectCollider = std::make_shared<CRectCollider>(30, 175);
    p2->cRectShape = std::make_shared<CRectShape>(30, 175, sf::Color::Blue, sf::Color::White, 0);

    auto p3 = m_entities.addEntity(PLATFORM);
    p3->cTransform = std::make_shared<CTransform>(Vec2(m_windowWidth - 400, m_windowHeight - 100));
    p3->cRectCollider = std::make_shared<CRectCollider>(30, 30);
    p3->cRectShape = std::make_shared<CRectShape>(30, 30, sf::Color::White, sf::Color::White, 0);
}

void Game::setPaused(bool paused)
{
    m_paused = paused;
}

void Game::sMovement()
{
    for (auto& e : m_entities.getEntities())
    {
        if (e->cTransform)
        {
            if (e->cRectCollider)
            {
                e->cRectCollider->shape.setPosition(e->cTransform->position.x, e->cTransform->position.y);
            }
            if (e->cCircleCollider)
            {
                e->cCircleCollider->shape.setPosition(e->cTransform->position.x, e->cTransform->position.y);
            }

            if (e->cGravity)
            {
                e->cTransform->velocity.y = std::min(50, (int) (e->cTransform->velocity.y + e->cGravity->acceleration));
            }
            e->cTransform->position += e->cTransform->velocity;
        }
    }
}

void Game::sAnimate()
{
    for (auto& e : m_entities.getEntities())
    {
        if (e->cTransform && e->cCircleShape)
        {
            e->cCircleShape->shape.setPosition(
                e->cTransform->position.x,
                e->cTransform->position.y
            );
            e->cCircleShape->shape.setRotation(e->cTransform->rotation);

            if (e->cLifespan)
            {
                e->cCircleShape->shape.setFillColor(sf::Color(
                    e->cCircleShape->shape.getFillColor().r,
                    e->cCircleShape->shape.getFillColor().g,
                    e->cCircleShape->shape.getFillColor().b,
                    255 * (e->cLifespan->remaining / e->cLifespan->total)
                ));
                e->cCircleShape->shape.setOutlineColor(sf::Color(
                    e->cCircleShape->shape.getOutlineColor().r,
                    e->cCircleShape->shape.getOutlineColor().g,
                    e->cCircleShape->shape.getOutlineColor().b,
                    255 * (e->cLifespan->remaining / e->cLifespan->total)
                ));
            }
        } else if (e->cTransform && e->cRectShape)
        {
            e->cRectShape->shape.setPosition(
                e->cTransform->position.x,
                e->cTransform->position.y
            );
            e->cRectShape->shape.setRotation(e->cTransform->rotation);

            if (e->cLifespan)
            {
                e->cRectShape->shape.setFillColor(sf::Color(
                    e->cRectShape->shape.getFillColor().r,
                    e->cRectShape->shape.getFillColor().g,
                    e->cRectShape->shape.getFillColor().b,
                    255 * (e->cLifespan->remaining / e->cLifespan->total)
                ));
                e->cRectShape->shape.setOutlineColor(sf::Color(
                    e->cRectShape->shape.getOutlineColor().r,
                    e->cRectShape->shape.getOutlineColor().g,
                    e->cRectShape->shape.getOutlineColor().b,
                    255 * (e->cLifespan->remaining / e->cLifespan->total)
                ));
            }
        }
    }
}

void Game::sUserInput()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                m_window.close();
                break;
            
            case sf::Event::KeyPressed:
                for (auto& e : m_entities.getEntities())
                {
                    if (e->cInput)
                    {
                        switch (event.key.code)
                        {
                            case sf::Keyboard::W:
                                e->cInput->up = true;
                                break;
                            case sf::Keyboard::A:
                                e->cInput->left = true;
                                break;
                            case sf::Keyboard::S:
                                e->cInput->down = true;
                                break;
                            case sf::Keyboard::D:
                                e->cInput->right = true;
                                break;
                            case sf::Keyboard::Space:
                                e->cInput->jump = true;
                                break;
                            case sf::Keyboard::Escape:
                                setPaused(!m_paused);
                            default:
                                break;
                        }
                    }
                }
                break;

            case sf::Event::KeyReleased:
                for (auto& e : m_entities.getEntities())
                {
                    if (e->cInput)
                    {
                        switch (event.key.code)
                        {
                            case sf::Keyboard::W:
                                e->cInput->up = false;
                                break;
                            case sf::Keyboard::A:
                                e->cInput->left = false;
                                break;
                            case sf::Keyboard::S:
                                e->cInput->down = false;
                                break;
                            case sf::Keyboard::D:
                                e->cInput->right = false;
                                break;
                            case sf::Keyboard::Space:
                                e->cInput->jump = false;
                                break;
                            default:
                                break;
                        }
                    }
                }
                break;

            default:
                break;
        }
    }
    // Why isn't this working in the event loop??
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        for (auto& e : m_entities.getEntities())
        {
            if (e->cInput)
            {
                e->cInput->place = true;
            }
        }
    } else
    {
        for (auto& e : m_entities.getEntities())
        {
            if (e->cInput)
            {
                e->cInput->place = false;
            }
        }
    }
}

void Game::sPlayerInput()
{
    for (auto& e : m_entities.getEntities())
    {
        if (e->cInput && e->cTransform)
        {
            float horizontalVel = 0.0f;
            if (e->cInput->left) horizontalVel += -1;
            if (e->cInput->right) horizontalVel += 1;
            horizontalVel *= 7;

            e->cTransform->velocity.x = horizontalVel;

            if (e->cInput->jump && e->cRectCollider->isCollidedBot) e->cTransform->velocity.y = -20.0f;

            if (e->cInput->place)
            {
                Vec2 mousePos = Vec2(sf::Mouse::getPosition(m_window).x,
                                     sf::Mouse::getPosition(m_window).y);
                if (m_placeCooldown == 0)
                {
                    srand(time(NULL));
                    auto p = m_entities.addEntity(PLATFORM);
                    p->cTransform = std::make_shared<CTransform>(mousePos);
                    p->cRectShape = std::make_shared<CRectShape>(100, 30,
                        sf::Color(rand() % 255, rand() % 255, rand() % 255, 255), sf::Color::White, 0);
                    p->cRectCollider = std::make_shared<CRectCollider>(100, 30);

                    m_placeCooldown = 60;
                }
            }
            m_placeCooldown = std::max(m_placeCooldown - 1, 0);
        }
    }
}

void Game::sLifespan()
{
    for (auto& e : m_entities.getEntities())
    {
        if (e->cLifespan)
        {
            e->cLifespan->remaining--;
            if (e->cLifespan->remaining <= 0) e->destroy();
        }
    }
}

void Game::sRender()
{
    bool showBoundingBoxes = false;

    for (auto& e : m_entities.getEntities())
    {
        if (e->cCircleShape)
            m_window.draw(e->cCircleShape->shape);
        if (e->cRectShape)
            m_window.draw(e->cRectShape->shape);

        if (showBoundingBoxes && e->cRectCollider)
        {
            m_window.draw(e->cRectCollider->shape);
        }
        if (showBoundingBoxes && e->cCircleCollider)
        {
            m_window.draw(e->cCircleCollider->shape);
        }
    }
}

void Game::sCollision()
{
    sPlayerCollision();
}

void Game::sPlayerCollision()
{
    m_player->cRectCollider->isCollidedBot = false;
    m_player->cRectCollider->isCollidedTop = false;
    m_player->cRectCollider->isCollidedLeft = false;
    m_player->cRectCollider->isCollidedRight = false;

    // Bottom of screen collision
    if (m_player->cTransform->position.y + m_player->cRectCollider->halfHeight > m_windowHeight)
    {
        m_player->cTransform->position.y = m_windowHeight - m_player->cRectCollider->halfHeight;
        m_player->cTransform->velocity.y = 0;
        m_player->cRectCollider->isCollidedBot = true;
    }
    for (auto& p : m_entities.getEntitiesByTag(PLATFORM))
    {
        if (p->cTransform && p->cRectCollider)
        {
            float dx = abs(m_player->cTransform->position.x - p->cTransform->position.x);
            float dy = abs(m_player->cTransform->position.y - p->cTransform->position.y);
            float ox = m_player->cRectCollider->halfWidth + p->cRectCollider->halfWidth - dx;
            float oy = m_player->cRectCollider->halfHeight + p->cRectCollider->halfHeight - dy;
            
            if (ox > 0 && oy > 0)
            {
                if (p->cRectCollider->prevOx > 0 && m_player->cTransform->position.y < p->cTransform->position.y) // Tp
                {    
                    m_player->cTransform->position.y -= oy;
                    m_player->cTransform->velocity.y = 0;
                    m_player->cRectCollider->isCollidedBot = true;

                } else if (p->cRectCollider->prevOx > 0 && m_player->cTransform->position.y > p->cTransform->position.y) // Bot
                {
                    m_player->cTransform->position.y += oy;
                    m_player->cTransform->velocity.y = 0;
                    m_player->cRectCollider->isCollidedTop = true;
                } else if (p->cRectCollider->prevOy > 0 && m_player->cTransform->position.x < p->cTransform->position.x) // Left
                {
                    m_player->cTransform->position.x -= ox;
                    m_player->cTransform->velocity.x = 0;
                    m_player->cRectCollider->isCollidedRight = true;
                } else if (p->cRectCollider->prevOy > 0 && m_player->cTransform->position.x > p->cTransform->position.x) // Right
                {
                    m_player->cTransform->position.x += ox;
                    m_player->cTransform->velocity.x = 0;
                    m_player->cRectCollider->isCollidedLeft = true;
                } else if (m_player->cTransform->position.x > p->cTransform->position.x) // Diagonal cases
                {
                    m_player->cTransform->position.x += ox;
                    m_player->cTransform->velocity.x = 0;
                    m_player->cRectCollider->isCollidedLeft = true;
                } else
                {
                    m_player->cTransform->position.x -= ox;
                    m_player->cTransform->velocity.x = 0;
                    m_player->cRectCollider->isCollidedRight = true;
                }
            } else
            {
                p->cRectCollider->prevOx = ox;
                p->cRectCollider->prevOy = oy;
            }
        }
    }
}

void Game::respawnPlayer()
{
    m_player->cTransform->position = Vec2(m_windowWidth / 2, m_windowHeight / 2);
}

void Game::sParentChild()
{
    for (auto& e : m_entities.getEntities())
    {
        if (e->cParentChild && e->cTransform && e->cParentChild->parent)
        {
            e->cTransform->position = e->cParentChild->parent->position;
        }
    }
}

void Game::spawnPlayer()
{
    m_player = m_entities.addEntity(PLAYER);

    float mx = m_windowWidth / 2;
    float my = m_windowHeight / 2;

    m_player->cTransform = std::make_shared<CTransform>(Vec2(50, 50));
    m_player->cRectShape = std::make_shared<CRectShape>(
        30, 30, sf::Color(0xFF0000FF), sf::Color(0xFF0000FF), 0
    );
    m_player->cRectShape->shape.setPosition(
        mx, my
    );
    m_player->cGravity = std::make_shared<CGravity>();
    m_player->cInput = std::make_shared<CInput>();
    m_player->cInvulnerable = std::make_shared<CInvulnerable>();
    m_player->cRectCollider = std::make_shared<CRectCollider>(30, 30);
}