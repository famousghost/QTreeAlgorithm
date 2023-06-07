#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

namespace McRenderer
{
    class Input
    {
    public:

        static void buttonsClick(sf::RenderWindow& p_window);
        static void move(sf::Vector2f& p_point, sf::Vector2f& p_direction, float p_deltaTime);
        static void rotate(sf::Vector2f& p_point, float p_deltaTime);
        static bool s_moveUp;
        static bool s_rotateLeft;
        static bool s_rotateRight;
        static bool s_moveDown;
        static bool s_increaseLen;
        static bool s_decreaseLen;
        static float s_speed;
        static float s_rotationSpeed;
        static bool s_fixedFov;
        static bool s_increaseFov;
        static bool s_decreaseFov;
    };
}//McRenderer
