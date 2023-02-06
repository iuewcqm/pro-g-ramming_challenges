#include <iostream>
#include <SFML/Graphics.hpp>
#include "point.h"
#include "link.h"
#include "solver.h"

#define WIDTH 1200
#define HEIGHT 1000

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Cloth simulation");
sf::Clock timer;

Solver solver;

int count_points_x = 100;
int count_points_y = 50;
int link_length = 10;

sf::Vector2f prev_mouse_pos;
sf::Vector2f mouse_pos;
bool need_cut = false;
bool need_avoid = false;

void update();
void update_mouse();
void remove_links();
void render();
void check_events();
void create_points();
void create_links();

int main() {
    create_points();
    create_links();
    
    window.setVerticalSyncEnabled(true);
    mouse_pos = prev_mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(window);

    while(window.isOpen()) {
        check_events();
        
        update();
        update_mouse();
        render();

        window.display(); 
        window.clear();
    }

    return 0;
}

void create_points() {
    const sf::Vector2f orig_pos = { 100.f , 100.f };
    for(int y = 0; y < count_points_y; y++) {
        for(int x = 0; x < count_points_x; x++) {
            const sf::Vector2f next_pos = { orig_pos.x + link_length*x, orig_pos.y + link_length*y*2 };
            Point point;
            point.position = point.old_position = next_pos;
            solver.points.push_back(point);
        }
    }
    for(int x = 0; x < count_points_x; x++)
        solver.points[x].is_static = true;
}

void create_links() {
    for(int x = 0; x < count_points_x; x++) {
        for(int y = 0; y < count_points_y-1; y++) { 
            Link link;
            link.point1 = &solver.points[y * count_points_x + x];
            link.point2 = &solver.points[(y+1) * count_points_x + x];
            link.max_dist = link_length+0.5f;
            solver.links.push_back(link);
        }   
    }
    for(int y = 0; y < count_points_y; y++) {
        for(int x = 0; x < count_points_x-1; x++) {
            Link link;
            link.point1 = &solver.points[y*count_points_x + x];
            link.point2 = &solver.points[y*count_points_x + x+1];
            link.max_dist = link_length+0.5f;
            solver.links.push_back(link);
        }
    }
}

void update() { 
    float dt = timer.getElapsedTime().asMilliseconds() / 100.f; 
    solver.update(dt);
    timer.restart();
}

void update_mouse() {
    if(need_cut)
        remove_links();
    if(need_avoid)
        solver.apply_avoid(mouse_pos, 20.f);
}

void remove_links() {
    for(int i = 0; i < solver.links.size(); i++) {
        const sf::Vector2f p1 = solver.links[i].point1->position;
        const sf::Vector2f p2 = solver.links[i].point2->position;
        const float p1_dist = calc_dist(p1, mouse_pos);
        const float p2_dist = calc_dist(p2, mouse_pos);
        const float length = calc_dist(p1, p2)/1.5;

        if(p1_dist < length && p2_dist < length) {
            solver.links.erase(solver.links.cbegin()+i);
        }
    }
}
void render() {
    const int links_count = solver.links.size();
    sf::VertexArray va(sf::PrimitiveType::Lines, 2*links_count); 
    for(int i = 0; i < links_count; i++) {
        const Link link = solver.links[i];
        va[2*i] = link.point1->position;
        va[2*i+1] = link.point2->position;
    }

    window.draw(va);
}

void check_events() {
    sf::Event event;
    
    prev_mouse_pos = mouse_pos;
    mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(window);

    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed)
            window.close();
        if(event.type == sf::Event::MouseButtonPressed) {
            if(event.mouseButton.button == sf::Mouse::Left)
                need_cut = true;
            if(event.mouseButton.button == sf::Mouse::Right)
                need_avoid = true;
        } 
        if(event.type == sf::Event::MouseButtonReleased) {
            if(event.mouseButton.button == sf::Mouse::Left)
                need_cut = false;
            if(event.mouseButton.button == sf::Mouse::Right)
                need_avoid = false;
        }
        if(event.type == sf::Event::KeyPressed) {
            if(event.key.code == sf::Keyboard::R) {
                solver.clear();    
                create_points();
                create_links();
            }
        } 
    }
}
