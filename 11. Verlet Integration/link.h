#pragma once

#include <SFML/Graphics.hpp>
#include "miscs.h"
#include "point.h"

struct Link {
    Point *point1;
    Point *point2;
    float max_dist;
    
    void update() {
        const sf::Vector2f axis = point1->position - point2->position;
        const float dist = calc_dist(axis); 
        if(dist > max_dist) {
            const sf::Vector2f n = axis / dist;
            const float delta = dist - max_dist;
            point1->position -= 0.5f * delta * n;
            point2->position += 0.5f * delta * n; 
        }
    }
};
