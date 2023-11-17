#include "Game.h"
#include "Player.h"
#include "Asteroid.h"

std::vector<Entity*> Game::entities{};
std::list <std::vector<Entity*>::const_iterator> Game::removeList{};
std::list <Entity*> Game::addList{};
float Game::asteroidSpawnTime{};

void Game::begin()
{
	entities.push_back(new Player());

	asteroidSpawnTime = ASTEROID_SPAWN_TIME;
}

void Game::update(sf::RenderWindow& window, float deltaTime)
{
    Game::addList.clear();
    Game::removeList.clear();
    window.clear();
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
}
