#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include "Input.h"
#include "Transformations.h"
#include "QuadTree.h"
#include <random>

int main()
{
    using namespace McRenderer;
    const unsigned int l_windowWidth = 1270;
    const unsigned int l_windowHeight = 720;
    std::string l_title = "QTreeAlgorithm";
    sf::RenderWindow m_window(sf::VideoMode{ l_windowWidth, l_windowHeight }, l_title, sf::Style::Default);
    float l_prevTime = 0.0f;
    float l_currentTime = 0.0f;
    sf::Clock clock;

    Bounds l_bounds(sf::Vector2f(l_windowWidth / 2, l_windowHeight / 2), sf::Vector2f(l_windowWidth / 2, l_windowHeight / 2));
    sf::RectangleShape l_rect;
    l_rect.setPosition(l_bounds.m_position - l_bounds.m_size);
    l_rect.setSize(l_bounds.m_size * 2.0f);

    Particle l_particle(sf::Vector2f(l_windowWidth / 2, l_windowHeight / 2), 1.0f);

    sf::CircleShape l_circleShape;

    l_circleShape.setPosition(l_particle.m_position - sf::Vector2f(l_particle.m_radius, l_particle.m_radius));
    l_circleShape.setRadius(l_particle.m_radius);
    l_circleShape.setFillColor(sf::Color::White);

    sf::CircleShape l_closestPoint;
    l_closestPoint.setPosition(sf::Vector2f(l_windowHeight / 2, l_windowHeight / 2));
    l_closestPoint.setRadius(2.0f);
    l_closestPoint.setFillColor(sf::Color::Green);

    float l_particleRadius = 3.0f;
    std::vector<Particle> l_particles;
    std::random_device l_rd; // obtain a random number from hardware
    std::mt19937 l_gen(l_rd()); // seed the generator
    std::uniform_int_distribution<> l_xDistr(l_particleRadius * 4.0f, l_windowWidth - l_particleRadius * 4.0f); // define the range
    std::uniform_int_distribution<> l_yDistr(l_particleRadius * 4.0f, l_windowHeight - l_particleRadius * 4.0f); // define the range
    for (int i = 0; i < 500; ++i)
    {
        l_particles.emplace_back(sf::Vector2f(l_xDistr(l_gen), l_yDistr(l_gen)), l_particleRadius);
    }
    float l_gravity = 9.81f;
    // float l_time = 1.0f;
    while (m_window.isOpen())
    {
        QuadTree l_quadTree(l_bounds, 4);
        sf::Time l_elapsed = clock.getElapsedTime();
        Input::buttonsClick(m_window);
        l_prevTime = l_currentTime;
        l_currentTime = l_elapsed.asSeconds();
        float l_deltaTime = l_currentTime - l_prevTime;
        m_window.clear();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            auto mousePos = sf::Mouse::getPosition(m_window);
            l_particles.emplace_back(sf::Vector2f(mousePos.x, mousePos.y), l_particleRadius);
            //l_time = 1.0f;
        }
        for (const auto& particle : l_particles)
        {
            l_quadTree.insert(particle);
        }
        l_quadTree.draw(m_window);
        for (const auto& particle : l_particles)
        {
            sf::CircleShape particleShape;
            particleShape.setPosition(particle.m_position);
            particleShape.setRadius(particle.m_radius);
            m_window.draw(particleShape);
        }
        m_window.display();
        //l_time -= l_deltaTime;
    }

    return 0;
}