#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdint>

struct Ball{
    sf::Vector2f position;
    sf::Vector2f velocity;
    float radius;
    sf::Color color;
    sf::Angle direction;
    sf::Texture* texture = nullptr;
    Ball(sf::Vector2f position, sf::Vector2f velocity, float radius, sf::Color color,sf::Angle direction)
        :position(position), velocity(velocity), radius(radius), color(color), direction(direction)
    {}

};

