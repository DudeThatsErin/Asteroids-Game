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

private:
	static float asteroidSpawnTime;
};

