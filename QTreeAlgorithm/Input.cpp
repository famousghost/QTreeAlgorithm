#include "Input.h"
#include "Transformations.h"
namespace McRenderer
{
    bool Input::s_moveUp = false;
    bool Input::s_moveDown = false;
    bool Input::s_increaseLen = false;
    bool Input::s_decreaseLen = false;
    bool Input::s_rotateLeft = false;
    bool Input::s_fixedFov = true;
    bool Input::s_rotateRight = false;
    float Input::s_speed = 200.0f;
    float Input::s_rotationSpeed = 100.0f;
    bool Input::s_increaseFov = false;
    bool Input::s_decreaseFov = false;

    void Input::buttonsClick(sf::RenderWindow& p_window)
    {
        sf::Event event;
        while (p_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                p_window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                p_window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
                {
                    s_moveUp = true;
                }
                if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
                {
                    s_moveDown = true;
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    s_rotateLeft = true;
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    s_rotateRight = true;
                }
                if (event.key.code == sf::Keyboard::R)
                {
                    s_fixedFov = false;
                }
                if (event.key.code == sf::Keyboard::U)
                {
                    s_increaseFov = true;
                }
                if (event.key.code == sf::Keyboard::J)
                {
                    s_decreaseFov = true;
                }
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
                {
                    s_moveUp = false;
                }
                if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
                {
                    s_moveDown = false;
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    s_rotateLeft = false;
                }
                if (event.key.code == sf::Keyboard::D)
                {
                    s_rotateRight = false;
                }
                if (event.key.code == sf::Keyboard::R)
                {
                    s_fixedFov = true;
                }
                if (event.key.code == sf::Keyboard::U)
                {
                    s_increaseFov = false;
                }
                if (event.key.code == sf::Keyboard::J)
                {
                    s_decreaseFov = false;
                }
            }
        }
    }

    void Input::move(sf::Vector2f& p_point, sf::Vector2f& p_direction, float p_deltaTime)
    {
        if (Input::s_moveUp)
        {
            p_point += p_direction * Input::s_speed * p_deltaTime;
        }
        if (Input::s_moveDown)
        {
            p_point -= p_direction * Input::s_speed * p_deltaTime;
        }
    }

    void Input::rotate(sf::Vector2f& p_point, float p_deltaTime)
    {
        if (Input::s_rotateLeft)
        {
            p_point = Transformations::rotate(p_point, -Input::s_rotationSpeed * p_deltaTime);
        }

        if (Input::s_rotateRight)
        {
            p_point = Transformations::rotate(p_point, Input::s_rotationSpeed * p_deltaTime);
        }
    }
}//McRenderer