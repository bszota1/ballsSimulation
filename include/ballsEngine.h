#pragma once
#include "../include/ball.h"
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>

class BallsEngine : public sf::Drawable, public sf::Transformable {
private:
    std::vector<Ball> balls;

    void handleCollisions(const float width, const float height) {
        for (size_t i = 0; i < balls.size(); ++i) {
            if (balls[i].position.x - balls[i].radius < 0) {
                balls[i].position.x = balls[i].radius;
                balls[i].velocity.x *= -1;
            } else if (balls[i].position.x + balls[i].radius > width) {
                balls[i].position.x = width - balls[i].radius;
                balls[i].velocity.x *= -1;
            }

            if (balls[i].position.y - balls[i].radius < 0) {
                balls[i].position.y = balls[i].radius;
                balls[i].velocity.y *= -1;
            } else if (balls[i].position.y + balls[i].radius > height) {
                balls[i].position.y = height - balls[i].radius;
                balls[i].velocity.y *= -1;
            }

            for (size_t j = i + 1; j < balls.size(); ++j) {
                const sf::Vector2f delta = balls[i].position - balls[j].position;
                const float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

                if (float minDist = balls[i].radius + balls[j].radius; distance < minDist && distance > 0) {
                    auto m1 = static_cast<float>(balls[i].weight);
                    auto m2 = static_cast<float>(balls[j].weight);

                    sf::Vector2f v1 = balls[i].velocity;
                    sf::Vector2f v2 = balls[j].velocity;

                    const sf::Vector2f normal = delta / distance;
                    const sf::Vector2f relativeVelocity = v1 - v2;
                    const float velocityAlongNormal = (relativeVelocity.x * normal.x + relativeVelocity.y * normal.y);
                    if (velocityAlongNormal > 0) continue;

                    const float impulse = (2.f * velocityAlongNormal) / (m1 + m2);

                    balls[i].velocity -= impulse * m2 * normal;
                    balls[j].velocity += impulse * m1 * normal;

                    float overlap = minDist - distance;
                    sf::Vector2f separation = normal * (overlap / 2.f);
                    balls[i].position += separation;
                    balls[j].position -= separation;
                }
            }
        }
    }

public:
    void generateBalls(int count, const sf::Vector2u windowSize) {
        balls.clear();

        const auto windowArea = static_cast<float>(windowSize.x * windowSize.y);
        const float targetAreaPerBall = (windowArea * 0.12f) / static_cast<float>(count);
        const float calculatedRadius = std::sqrt(targetAreaPerBall / 3.1415f);
        float finalRadius = std::clamp(calculatedRadius, 5.f, 40.f);

        std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<float> posX(finalRadius, windowSize.x - finalRadius);
        std::uniform_real_distribution<float> posY(finalRadius, windowSize.y - finalRadius);
        std::uniform_real_distribution<float> vel(-200.f, 200.f);
        std::uniform_int_distribution<int> colorDist(100, 255);
        std::uniform_int_distribution<std::uint32_t> weightDist(10, 100);

        for (int i = 0; i < count; ++i) {
            sf::Color randomColor(colorDist(gen), colorDist(gen), colorDist(gen));
            sf::Vector2f pos(posX(gen), posY(gen));
            sf::Vector2f v(vel(gen), vel(gen));
            std::uint32_t weight = weightDist(gen);

            balls.emplace_back(pos, v, finalRadius, randomColor, sf::degrees(0), weight);
        }
    }

    void update(const float dt, const sf::Vector2u windowSize) {
        for (auto& ball : balls) {
            ball.position += ball.velocity * dt;
        }
        handleCollisions(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();
        sf::CircleShape shape;
        for (const auto& ball : balls) {
            shape.setRadius(ball.radius);
            shape.setFillColor(ball.color);
            shape.setOrigin({ball.radius, ball.radius});
            shape.setPosition(ball.position);
            target.draw(shape, states);
        }
    }
};