#pragma once
#include "Entity.h"

constexpr float PLAYER_W = 50.0f;
constexpr float PLAYER_H = 40.0f;
constexpr float TURN_SPEED = 200.0f;
constexpr float PLAYER_SPEED = 200.0f;

class Player : public Entity {
public:
    Player();

    void update(float deltaTime) override;

    void render(sf::RenderWindow& window) override;

private:
    sf::VertexArray array;
    float shootTimer;
};