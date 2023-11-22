#pragma once

#include "Components.h"
#include <memory>

enum Tag
{
    PLAYER,
    ENEMY,
    TILE,
    PROJECTILE,
    DEFAULT
};

class Entity
{
    const size_t m_id;
    const Tag    m_tag   = DEFAULT;
    bool         m_alive = true;

    friend class EntityManager;

    Entity(const Tag tag, size_t id) :
        m_tag(tag),
        m_id(id)
    {}

public:

    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CShape>     cShape;

    const size_t id() const;
    const Tag tag() const;
    void destroy();
    bool isAlive() const;
};