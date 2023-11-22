#include "Asteroid.h"
#include <random>
#include <iostream>
#include <type_traits>
static std::mt19937 gen(std::random_device{}());

Asteroid::Asteroid(sf::Vector2f direction, sf::Vector2f position)
    : Entity(position, 0), direction(direction), array(sf::LinesStrip, 11), life() {
    array[0].position = sf::Vector2f(-40, 40);
    array[1].position = sf::Vector2f(-50, 10);
    array[2].position = sf::Vector2f(-10, -20);
    array[3].position = sf::Vector2f(-20, -40);
    array[4].position = sf::Vector2f(10, -40);
    array[5].position = sf::Vector2f(40, -20);
    array[6].position = sf::Vector2f(40, -10);
    array[7].position = sf::Vector2f(0, 0);
    array[8].position = sf::Vector2f(40, 20);
    array[9].position = sf::Vector2f(0, 30);
    array[10].position = array[0].position; // closes the asteroid; without this the asteroid has an open spot; only needed for LinesStrip

    for (size_t i = 0; i < array.getVertexCount(); i++) {
        array[i].color = sf::Color::White;
    }
}

void Asteroid::update(float deltaTime)
{
    life += deltaTime;
    position += ASTEROID_SPEED * direction * deltaTime;
    angle += ASTEROID_SPIN * deltaTime;

    // bounce asteroids on edges of screen
    if (position.x < ASTEROID_W / 2.0f) {
        direction.x = abs(direction.x);
    }
    else if (position.x > SCREEN_WIDTH - ASTEROID_W / 2.0f) {
        direction.x = -abs(direction.x);
    }

    if (position.y < ASTEROID_H / 2.0f) {
        direction.y = abs(direction.y);
    }
    else if (position.y > SCREEN_HEIGHT - ASTEROID_H / 2.0f) {
        direction.y = -abs(direction.y);
    }
}

void Asteroid::render(sf::RenderWindow& window)
{
    window.draw(array, sf::Transform().translate(position).rotate(angle));
}

const sf::VertexArray& Asteroid::getVertexArray() const
{
    return array;
}

template<typename T>
T generate(T lower, T upper)
{
    if constexpr (std::is_floating_point_v<T>)
    {
        return std::uniform_real_distribution<T>{ lower, upper }(gen);
    }
    else
    {
        return std::uniform_int_distribution<T>{ lower, upper }(gen);
    }
}

// makes asteroids go in random directions
sf::Vector2f Asteroid::getRandomDirection()
{
    float angle = generate(0.0f, 2.0f * M_PI);
    return sf::Vector2f(cos(angle), sin(angle));
}

// makes asteroids spawn at random positions
sf::Vector2f Asteroid::getRandomPosition()
{
    int side = generate(0, 4);
    std::cout << "Side: " << side << std::endl;
    float xAxis, yAxis;
    if (side == 0) {
        xAxis = 0;
        yAxis = generate(0.0f, SCREEN_HEIGHT);
        return sf::Vector2f(xAxis, yAxis);
    }
    else if (side == 1)
    {
        xAxis = SCREEN_WIDTH;
        yAxis = generate(0.0f, SCREEN_HEIGHT);
        return sf::Vector2f(xAxis, yAxis);
    }
    else if (side == 2) {
        xAxis = 0;
        yAxis = generate(0.0f, SCREEN_HEIGHT);
        return sf::Vector2f(xAxis, yAxis);
    }
    else if (side == 4)
    {
        xAxis = SCREEN_WIDTH;
        yAxis = generate(0.0f, SCREEN_HEIGHT);
        return sf::Vector2f(xAxis, yAxis);
    }
}
