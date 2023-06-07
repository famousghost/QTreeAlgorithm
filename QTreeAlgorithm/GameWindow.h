#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

namespace McRenderer
{
    class GameWindow
    {
    public:
        GameWindow(unsigned int p_width, unsigned int p_height, unsigned int p_sidebarSize, std::string p_title, unsigned int p_style);

        static unsigned int getWitdth();

        static unsigned int getHeight();

        static unsigned int getSidebarSize();

        sf::RenderWindow& getWindow();

    private:
        static unsigned int s_width;
        static unsigned int s_height;
        static unsigned int s_sidebarSize;
        sf::RenderWindow m_window;
    };
}//McRenderer
