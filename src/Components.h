#pragma once

#include <SFML/Graphics.hpp>
#include "Vec2.h"

class CTransform
{
public:

    Vec2  position = Vec2::ZERO;
    Vec2  velocity = Vec2::ZERO;
    float rotation = 0.0f;

    CTransform() {};
    CTransform(Vec2 position, Vec2 velocity, float rotation) :
        position(position),
        velocity(velocity),
        rotation(rotation)
    {}
    CTransform(Vec2 position, Vec2 velocity) :
        position(position),
        velocity(velocity)
    {}
    CTransform(Vec2 position) :
        position(position)
    {}
};

class CGravity
{
public:

    float acceleration = 1.0f;

    CGravity() {};

    CGravity(float acceleration) :
        acceleration(acceleration)
    {}
};

class CCircleShape
{
public:

    sf::CircleShape shape;
    int             sideCount;

    CCircleShape(float radius, int sideCount, const sf::Color& fill,
           const sf::Color& outline, float outlineThickness) :
        shape(radius, sideCount),
        sideCount(sideCount)
    {
        shape.setFillColor(fill);
        shape.setOutlineColor(outline);
        shape.setOutlineThickness(outlineThickness);
        shape.setOrigin(radius, radius);
    }
};

class CRectShape
{
public:

    sf::RectangleShape shape;

    CRectShape(float width, float height, const sf::Color& fill,
           const sf::Color& outline, float outlineThickness) :
        shape(sf::Vector2f(width, height))
    {
        shape.setFillColor(fill);
        shape.setOutlineColor(outline);
        shape.setOutlineThickness(outlineThickness);
        shape.setOrigin(sf::Vector2f(width / 2, height / 2));
    }
};

class CInput
{
public:

    bool isLocked = false;
    bool up       = false;
    bool down     = false;
    bool left     = false;
    bool right    = false;
    bool place    = false;
    bool jump     = false;
};

class CLifespan
{
public:

    float total = 0.0f;
    float remaining = 0.0f;

    CLifespan(float total) :
        total(total),
        remaining(total)
    {}
};

class CCircleCollider
{
public:

    float radius = 0.0f;

    sf::CircleShape shape;
    bool showCollider = false;

    CCircleCollider(float radius) :
        radius(radius)
    {
        shape.setRadius(radius - 1);
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Green);
        shape.setOutlineThickness(1);
        shape.setOrigin(sf::Vector2f(radius / 2, radius / 2));
    }
};

class CRectCollider
{
public:

    float width  = 0.0f;
    float height = 0.0f;

    float halfWidth  = 0.0f;
    float halfHeight = 0.0f;

    bool isFixed = false;

    bool isCollidedTop   = false;
    bool isCollidedBot   = false;
    bool isCollidedLeft  = false;
    bool isCollidedRight = false;

    sf::RectangleShape shape;
    bool showCollider = false;

    CRectCollider(float width, float height) :
        width(width),
        height(height),
        halfWidth(width / 2),
        halfHeight(height / 2)
    {
        shape.setSize(sf::Vector2f(width - 1, height - 1));
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Green);
        shape.setOutlineThickness(1);
        shape.setOrigin(sf::Vector2f(width / 2, height / 2));
    }
};

class CInvulnerable
{
public:
    
    bool isInvulnerable = false;

    CInvulnerable() {}
};

class CParentChild
{
public:

    std::shared_ptr<CTransform> parent;

    CParentChild(std::shared_ptr<CTransform> parent) :
        parent(parent)
    {}
};