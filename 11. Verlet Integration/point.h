#pragma once

#include <SFML/Graphics.hpp>

struct Point {
    sf::Vector2f position;
    sf::Vector2f old_position;
    sf::Vector2f acceleration;
    bool is_static = false;

    void update(float dt) {
        sf::Vector2f velocity = position - old_position;
        old_position = position; 
        position = position + velocity + acceleration * dt * dt;
        acceleration = {};
    }

    void accelerate(sf::Vector2f acc) 
    {
        acceleration += acc;
    }
};
