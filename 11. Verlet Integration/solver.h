#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "point.h"
#include "link.h"
#include "miscs.h"

struct Solver {
    sf::Vector2f G = {0.f, 9.8f};

    std::vector<Point> points;
    std::vector<Link> links; 

    void update(float dt) {
        update_links();
        apply_gravity();
        update_positions(dt);
    }
    
    void apply_gravity() {
        for(Point &p : points)
            p.accelerate(G);
    }
    
    void update_positions(float dt) {
        for(Point &p : points) {
            if(!p.is_static)
                p.update(dt); 
            else
                p.position = p.old_position;      
        }
    }
    
    void update_links() {
        for(int i = 0; i < links.size(); i++) {
            const float dist = calc_dist(links[i].point1->position, links[i].point2->position);  
            if(dist > links[i].max_dist * 4)
                links.erase(links.cbegin()+i); 
            links[i].update();     
        }
    }
    
    void apply_avoid(sf::Vector2f pos, float radius) { 
        for(Point &p : points) {
            const sf::Vector2f to_point = p.position - pos;
            const float dist = calc_dist(to_point);
            if(dist < radius) {
                const sf::Vector2f n = to_point / dist;
                const float delta = radius - dist;
                p.position += 0.5f * delta * n;
            }
        }
    }
    
    void clear() {
        points.clear();
        links.clear();
    }
};
