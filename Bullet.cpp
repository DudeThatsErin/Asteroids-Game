#include "Bullet.h"
#include "Game.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction)
	: shape(1.0f), direction(direction), Entity(position, 0.0f), lifeTime(BULLET_LIFE) {}

void Bullet::update(float deltaTime)
{
    lifeTime -= deltaTime;
    position += direction * BULLET_SPEED * deltaTime;
    if (lifeTime <= 0.0f) {
        Game::removeList.push_back(std::find(Game::entities.begin(), Game::entities.end(), this));
    }
}

void Bullet::render(sf::RenderWindow& window)
{
    window.draw(shape, sf::Transform().translate(position));
}