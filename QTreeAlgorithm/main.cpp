#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include "Input.h"
#include "Transformations.h"

int main()
{
    const unsigned int l_windowWidth = 800;
    const unsigned int l_windowHeight = 400;
    std::string l_title = "QTreeAlgorithm";
    sf::RenderWindow m_window(sf::VideoMode{ l_windowWidth, l_windowHeight }, l_title, sf::Style::Default);
    static double l_time = 0.1;
    float l_prevTime = 0.0f;
    float l_currentTime = 0.0f;
    sf::Clock clock;
    while (m_window.isOpen())
    {
        sf::Time l_elapsed = clock.getElapsedTime();
        l_prevTime = l_currentTime;
        l_currentTime = l_elapsed.asSeconds();
        float l_deltaTime = l_currentTime - l_prevTime;
        m_window.clear();
        Input::buttonsClick(m_window);

        m_window.display();
    }

    return 0;
}