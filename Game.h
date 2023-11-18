#pragma once
#include <vector>
#include <list>
#include "Entity.h"

class Game
{
public:
	static void begin();
	static void update(sf::RenderWindow& window, float deltaTime);

	static std::vector<Entity*> entities;
	static std::list <std::vector<Entity*>::const_iterator> removeList;
	static std::list <Entity*> addList;

	static size_t score;

private:
	static float asteroidSpawnTime;
	static float tAsteroidSpawnTime;
	static sf::Text scoreText;
	static sf::Font font;
};

