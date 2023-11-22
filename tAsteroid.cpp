#include <random>
#include <iostream>
#include <type_traits>
#include "tAsteroid.h"
static std::mt19937 gen(std::random_device{}());

tAsteroid::tAsteroid(sf::Vector2f direction, sf::Vector2f position)
    : Entity(position, 0), direction(direction), array(sf::LinesStrip, 11), tLife() {
    array[0].position = sf::Vector2f(-100, 100);
    array[1].position = sf::Vector2f(-50, 50);
    array[2].position = sf::Vector2f(-80, -60);
    array[3].position = sf::Vector2f(-10, -10);
    array[4].position = sf::Vector2f(15, -15);
    array[5].position = sf::Vector2f(40, -20);
    array[6].position = sf::Vector2f(40, -10);
    array[7].position = sf::Vector2f(0, 0);
    array[8].position = sf::Vector2f(80, 60);
    array[9].position = sf::Vector2f(0, 40);
    array[10].position = array[0].position; // closes the asteroid; without this the asteroid has an open spot; only needed for LinesStrip

    for (size_t i = 0; i < array.getVertexCount(); i++) {
        array[i].color = sf::Color::White;
    }
}

void tAsteroid::update(float deltaTime)
{
    tLife += deltaTime;
    position += tASTEROID_SPEED * direction * deltaTime;
    angle += tASTEROID_SPIN * deltaTime;

    // bounce asteroids on edges of screen
    if (position.x < tASTEROID_W / 2.0f) {
        direction.x = abs(direction.x);
    }
    else if (position.x > SCREEN_WIDTH - tASTEROID_W / 2.0f) {
        direction.x = -abs(direction.x);
    }

    if (position.y < tASTEROID_H / 2.0f) {
        direction.y = abs(direction.y);
    }
    else if (position.y > SCREEN_HEIGHT - tASTEROID_H / 2.0f) {
        direction.y = -abs(direction.y);
    }
}

void tAsteroid::render(sf::RenderWindow& window)
{
    window.draw(array, sf::Transform().translate(position).rotate(angle));
}

const sf::VertexArray& tAsteroid::getVertexArray() const
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
sf::Vector2f tAsteroid::getRandomDirection()
{
    float angle = generate(0.0f, 2.0f * M_PI);
    return sf::Vector2f(cos(angle), sin(angle));
}

// makes asteroids spawn at random positions
sf::Vector2f tAsteroid::getRandomPosition()
{
    float xAxis = generate(tASTEROID_W / 2.0f, SCREEN_WIDTH - tASTEROID_W / 2.0f);
    float yAxis = generate(tASTEROID_H / 2.0f, SCREEN_HEIGHT - tASTEROID_H / 2.0f);

    return sf::Vector2f(xAxis, yAxis);
}
