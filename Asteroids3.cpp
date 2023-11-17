#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Asteroids", sf::Style::Close | sf::Style::Titlebar);
    sf::Clock clock;

    Game::begin();

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        sf::Event e{};
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
        }
        Game::update(window, deltaTime);

        window.display();
    }
}