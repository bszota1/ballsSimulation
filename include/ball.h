#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>
struct Ball{
    sf::Vector2f position;
    sf::Vector2f velocity;
    float radius;
    sf::Color color;
    sf::Angle direction;
    sf::Texture* texture = nullptr;
    std::uint32_t weight;

    Ball(sf::Vector2f position, sf::Vector2f velocity, float radius, sf::Color color,sf::Angle direction, std::uint32_t weight)
        :position(position),
        velocity(velocity),
        radius(radius),
        color(color),
        direction(direction),
        weight(weight)
    {}
};

