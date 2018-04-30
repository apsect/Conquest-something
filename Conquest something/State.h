#pragma once

//#include "GlobalDef.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

class State
{
public:
	State(sf::RenderWindow& a_window) :
		m_window(a_window)
	{
		m_window.setVerticalSyncEnabled(true);
		m_window.setFramerateLimit(60);
	}

	virtual std::unique_ptr<State> run() = 0;

protected:
	virtual void update() = 0;
	virtual void render() = 0;

protected:
	sf::RenderWindow& m_window;
};