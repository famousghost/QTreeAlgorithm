#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include "Input.h"
#include "Transformations.h"
#include "QuadTree.h"
#include <random>

#define DRAW_QTREE 1
#define QTREE 1
#define DEBUG 0
#define FPS 1

#define PARTICLES_COUNT 1000

int main()
{
    using namespace McRenderer;
    const unsigned int l_windowWidth = 800;
    const unsigned int l_windowHeight = 600;
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

    float l_particleRadius = 6.0f;
    std::vector<Particle> l_particles;
    std::random_device l_rd; // obtain a random number from hardware
    std::mt19937 l_gen(l_rd()); // seed the generator
    std::uniform_int_distribution<> l_xDistr(l_particleRadius * 4.0f, l_windowWidth - l_particleRadius * 4.0f); // define the range
    std::uniform_int_distribution<> l_yDistr(l_particleRadius * 4.0f, l_windowHeight - l_particleRadius * 4.0f); // define the range
    for (int i = 0; i < PARTICLES_COUNT; ++i)
    {
        l_particles.emplace_back(sf::Vector2f(l_xDistr(l_gen), l_yDistr(l_gen)), l_particleRadius);
    }
    float l_gravity = 9.81f;

    sf::CircleShape particleShape;
    sf::RectangleShape l_checkBoundsShape;

    float l_friction = 0.9997f;
    sf::Vector2f l_acceleration(0.0f, 100.0f);
    while (m_window.isOpen())
    {
        sf::Time l_elapsed = clock.getElapsedTime();
        Input::buttonsClick(m_window);
        l_prevTime = l_currentTime;
        l_currentTime = l_elapsed.asSeconds();
        float l_deltaTime = l_currentTime - l_prevTime;
        m_window.clear();

        std::vector<Particle> l_intersectionParticles;

        int l_counter = 0;

        QuadTree l_quadTree(l_bounds, 4);
        for (const auto& particle : l_particles)
        {
            l_quadTree.insert(particle);
        }
#if DRAW_QTREE
        l_quadTree.draw(m_window);
#endif

        for (int i = 0; i < PARTICLES_COUNT; ++i)
        {
            auto& p = l_particles[i];

            if ((p.m_position.y + p.m_radius) > l_windowHeight)
            {
                p.m_velocity.y = p.m_velocity.y * -1.0f;
                p.m_position.y = l_windowHeight - p.m_radius;
            }
            if ((p.m_position.y - p.m_radius) < 0.0f)
            {
                p.m_velocity.y = p.m_velocity.y * -1.0f;
                p.m_position.y = p.m_radius;
            }
            if ((p.m_position.x + p.m_radius) > l_windowWidth)
            {
                p.m_velocity.x = p.m_position.x * -1.0f;
                p.m_position.x = l_windowWidth - p.m_radius;
            }
            if ((p.m_position.x - p.m_radius) < 0.0f)
            {
                p.m_velocity.x = p.m_velocity.x * -1.0f;
                p.m_position.x = p.m_radius;
            }

#if QTREE
            //float t = clock.getElapsedTime().asSeconds();
            //efficent way to calculate collisions
            Bounds l_particleBound(p.m_position, sf::Vector2f(p.m_radius * 2.0f, p.m_radius * 2.0f));
            l_quadTree.getAllIntersectingPoints(l_particleBound, l_intersectionParticles, l_counter);
            for (auto& particle : l_intersectionParticles)
            {
                auto dir = p.collision(particle);

                if (dir == sf::Vector2f())
                {
                    continue;
                }

                p.m_velocity += dir;
                p.m_velocity *= l_friction;
            }
            //std::cout << clock.getElapsedTime().asSeconds() - t << "\n";
#else

            //inefficent way to calculate collisions
            //float t = clock.getElapsedTime().asSeconds();
            for (auto& particle : l_particles)
            {
                l_counter++;
                auto dir = p.collision(particle);

                if (dir == sf::Vector2f())
                {
                    continue;
                }

                p.m_velocity += dir;
                p.m_velocity *= l_friction;
            }
            //std::cout << clock.getElapsedTime().asSeconds() - t << "\n";
#endif

            p.m_velocity += (l_acceleration * l_deltaTime);
            p.m_velocity *= l_friction;
            p.update(l_deltaTime);

            particleShape.setPosition(p.m_position.x, p.m_position.y);
            particleShape.setFillColor(sf::Color::White);
            particleShape.setRadius(p.m_radius);
            m_window.draw(particleShape);
        }
#if DEBUG
        std::cout << l_counter << "\n";
#endif

        m_window.display();

#if FPS
        float fps = 1.f / l_deltaTime;
        std::cout << fps << "\n";
#endif
    }

    return 0;
}