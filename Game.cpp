#include "Game.h"
#include "Player.h"
#include "Asteroid.h"
#include "tAsteroid.h"
#include <iostream>

std::vector<Entity*> Game::entities{};
std::list <std::vector<Entity*>::const_iterator> Game::removeList{};
std::list <Entity*> Game::addList{};
float Game::asteroidSpawnTime{};
float Game::tAsteroidSpawnTime{};
size_t Game::score{};
sf::Text Game::scoreText{};
sf::Font Game::font{};



void Game::begin()
{

    font.loadFromFile("arial.ttf");

    scoreText.setFont(font);
    scoreText.setPosition(sf::Vector2f(40, 20));
    scoreText.setCharacterSize(60);

	entities.push_back(new Player());
    tAsteroidSpawnTime = tASTEROID_SPAWN_TIME;
	asteroidSpawnTime = ASTEROID_SPAWN_TIME;
}

void Game::update(sf::RenderWindow& window, float deltaTime)
{
    Game::addList.clear();
    Game::removeList.clear();
    window.clear();
    tAsteroidSpawnTime -= deltaTime;
    asteroidSpawnTime -= deltaTime;

    Game::addList.clear();
    Game::removeList.clear();
    window.clear();

    for (size_t i = 0; i < Game::entities.size(); i++) {
        Game::entities[i]->update(deltaTime);
        Game::entities[i]->render(window);
    }
    // remove items from list; prevents memory leaks
    for (const auto& it : Game::removeList) {
        delete* it;
        Game::entities.erase(it);
    }

    // add items to list; helps prevent memory leaks
    for (auto& ptr : Game::addList) {
        Game::entities.push_back(ptr);
    }

    // create more than 1 asteroid at a time
    if (asteroidSpawnTime <= 0.0f) {
        Game::entities.push_back(new Asteroid());
        asteroidSpawnTime = ASTEROID_SPAWN_TIME;
    }
    
    // create more than 1 triangular asteroid at a time
    if (tAsteroidSpawnTime <= 0.0f) {
        Game::entities.push_back(new tAsteroid());
        tAsteroidSpawnTime = tASTEROID_SPAWN_TIME;
    }
    scoreText.setString(std::to_string(score));
    window.draw(scoreText);
}
