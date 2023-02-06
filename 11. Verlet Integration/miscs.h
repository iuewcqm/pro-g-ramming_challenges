#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

sf::Vector2f G(0.f, 9.8f);

float calc_dist(sf::Vector2f s_vec, sf::Vector2f f_vec) {
    return sqrt(pow(s_vec.x - f_vec.x, 2) + pow(s_vec.y - f_vec.y, 2));
}
float calc_dist(sf::Vector2f axis) {
    return sqrt(pow(axis.x, 2) + pow(axis.y, 2));
}