#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>

class Application
{
public:
	Application();
	void run();

private:
	sf::RenderWindow m_window;
	sf::Image m_icon;
};