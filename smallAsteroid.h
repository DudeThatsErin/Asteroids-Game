#pragma once
#include "Global.h"

class smallAsteroid {
public:
    smallAsteroid() : smallAsteroid({ 0,0 }, 0.0f) {}
    smallAsteroid(sf::Vector2f position, float angle) : position(position), angle(angle) {}
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual ~smallAsteroid();
    sf::Vector2f position;
    float angle;
};