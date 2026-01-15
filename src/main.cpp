#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "../include/ballsEngine.h"

int main(int argc, char* argv[]) {
    int numBalls = 15;

    if (argc > 1) {
        try {
            numBalls = std::stoi(argv[1]);
            if (numBalls <= 0) throw std::invalid_argument("Quantity must be positive");
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    } else {
        std::cout << "User didnt input balls quantity" << argv[0] << " [balls_quantity]" << std::endl;
    }

    sf::RenderWindow window(sf::VideoMode({1200, 1000}), "Balls Simulator");
    window.setFramerateLimit(60);

    BallsEngine engine;
    engine.generateBalls(numBalls, window.getSize());

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        engine.update(dt, window.getSize());

        window.clear(sf::Color(15, 15, 25));
        window.draw(engine);
        window.display();
    }

    return 0;
}