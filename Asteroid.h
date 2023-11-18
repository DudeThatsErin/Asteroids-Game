#pragma once
#include "Entity.h"

constexpr float ASTEROID_W = 90.0f;
constexpr float ASTEROID_H = 80.0f;
constexpr float ASTEROID_SPIN = 25.0f;
constexpr float ASTEROID_SPEED = 280.0f;
constexpr float ASTEROID_SPAWN_TIME = 1.0f;

class Asteroid : public Entity {
public:
    Asteroid(sf::Vector2f direction = Asteroid::getRandomDirection());

    void update(float deltaTime) override;

    void render(sf::RenderWindow& window) override;

    const sf::VertexArray& getVertexArray() const;

    // moves asteroids in random directions
    static sf::Vector2f getRandomDirection();

    // spawns asteroids at random positions
    static sf::Vector2f getRandomPosition();




private:
    sf::VertexArray array;
    sf::Vector2f direction;
};