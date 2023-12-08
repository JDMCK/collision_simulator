#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "EntityManager.h"
#include "Components.h"

class Game
{
    sf::RenderWindow m_window; 
    EntityManager    m_entities;
    sf::Font         m_font;
    int              m_windowWidth;
    int              m_windowHeight;
    bool             m_paused = false;
    bool             m_running = true;
    int              m_placeCooldown = 0;

    std::shared_ptr<Entity> m_player;

    void init();
    void setPaused(bool paused);

    void sMovement();
    void sAnimate();
    void sUserInput();
    void sPlayerInput();
    void sLifespan();
    void sRender();
    void sCollision();
    void sPlayerCollision();
    void sParentChild();

    void respawnPlayer();
    void spawnPlayer();
    void spawnPlatforms();

public:

    void run();

    Game();
};
