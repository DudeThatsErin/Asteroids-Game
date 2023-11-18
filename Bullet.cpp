#include "Bullet.h"
#include "Game.h"
#include "Asteroid.h"
#include "Physics.h"
#include "tAsteroid.h"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction)
	: shape(1.0f), direction(direction), Entity(position, 0.0f), lifeTime(BULLET_LIFE) {}

void Bullet::update(float deltaTime)
{
    lifeTime -= deltaTime;
    position += direction * BULLET_SPEED * deltaTime;
    if (lifeTime <= 0.0f) {
        Game::removeList.push_back(std::find(Game::entities.begin(), Game::entities.end(), this));
    }

    for (size_t i = 0; i < Game::entities.size(); i++) {
        if (typeid(*Game::entities[i]) == typeid(Asteroid)) {
            Asteroid* asteroid = dynamic_cast<Asteroid*>(Game::entities[i]);
            sf::Transform transform = sf::Transform().translate(asteroid->position).rotate(asteroid->angle);
            
            if (physics::intersects(position, physics::getTransformed(asteroid->getVertexArray(), transform))) {
                lifeTime = 0.0f;
                Game::removeList.push_back(std::find(Game::entities.begin(), Game::entities.end(), asteroid));
                Game::score += 10;
            }
        }
        if (typeid(*Game::entities[i]) == typeid(tAsteroid)) {
            tAsteroid* tasteroid = dynamic_cast<tAsteroid*>(Game::entities[i]);
            sf::Transform transform = sf::Transform().translate(tasteroid->position).rotate(tasteroid->angle);

            if (physics::intersects(position, physics::getTransformed(tasteroid->getVertexArray(), transform))) {
                lifeTime = 0.0f;
                Game::removeList.push_back(std::find(Game::entities.begin(), Game::entities.end(), tasteroid));
                Game::score += 50;
            }
        }
    }
}

void Bullet::render(sf::RenderWindow& window)
{
    window.draw(shape, sf::Transform().translate(position));
}