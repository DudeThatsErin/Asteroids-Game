#include "Player.h"
#include "Bullet.h"
#include "Game.h"

Player::Player()
    : Entity(sf::Vector2f(500, 500), 0), array(sf::Quads, 4), shootTimer() {
    array[0].position = sf::Vector2f(20, 0); // top
    array[1].position = sf::Vector2f(-20, -20); // bottom left
    array[2].position = sf::Vector2f(-10, 0); // middle
    array[3].position = sf::Vector2f(-20, 20); // bottom right

    for (size_t i = 0; i < array.getVertexCount(); i++) {
        array[i].color = sf::Color::White;
    }
}

void Player::update(float deltaTime)
{
    shootTimer -= deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { // left
        angle -= TURN_SPEED * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { // right
        angle += TURN_SPEED * deltaTime;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { // forward
        float radians = angle * (M_PI / 180.0f);

        position.x += cos(radians) * PLAYER_SPEED * deltaTime;
        position.y += sin(radians) * PLAYER_SPEED * deltaTime;

        position.x = std::min(std::max(position.x, PLAYER_W / 2.0f), SCREEN_WIDTH - PLAYER_W / 2.0f);
        position.y = std::min(std::max(position.y, PLAYER_H / 2.0f), SCREEN_HEIGHT - PLAYER_H / 2.0f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // backward
        float radians = angle * (M_PI / 180.0f);

        position.x -= cos(radians) * PLAYER_SPEED * deltaTime;
        position.y -= sin(radians) * PLAYER_SPEED * deltaTime;

        position.x = std::min(std::max(position.x, PLAYER_W / 2.0f), SCREEN_WIDTH - PLAYER_W / 2.0f);
        position.y = std::min(std::max(position.y, PLAYER_H / 2.0f), SCREEN_HEIGHT - PLAYER_H / 2.0f);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootTimer <= 0.0f) { // Shooting
        shootTimer = SHOOT_DELAY;
        float radians = angle * (M_PI / 180.0f);

        Game::addList.push_back(
            new Bullet(position, sf::Vector2f(cos(radians), sin(radians)))
        );
    }
}

void Player::render(sf::RenderWindow& window)
{
    window.draw(array, sf::Transform().translate(position).rotate(angle));
}