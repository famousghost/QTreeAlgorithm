#include "GameWindow.h"

unsigned int GameWindow::s_width = 0;
unsigned int GameWindow::s_height = 0;
unsigned int GameWindow::s_sidebarSize = 0;

GameWindow::GameWindow(unsigned int p_width, unsigned int p_height, unsigned int p_sidebarSize, std::string p_title, unsigned int p_style)
    : m_window(sf::VideoMode{p_width, p_height}, p_title, p_style)
{
    s_width = p_width;
    s_height = p_height;
    s_sidebarSize = p_sidebarSize;
}

unsigned int GameWindow::getWitdth()
{
    return s_width;
}

unsigned int GameWindow::getHeight()
{
    return s_height;
}

unsigned int GameWindow::getSidebarSize()
{
    return s_sidebarSize;
}

sf::RenderWindow& GameWindow::getWindow()
{
    return m_window;
}
