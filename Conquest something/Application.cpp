#include "Application.h"
#include "State.h"
#include "MenuState.h"
#include "PlayState.h"

#include <memory>

Application::Application() :
	m_window(sf::VideoMode(1024, 768), "Conquest smth", sf::Style::Titlebar | sf::Style::Close)
{
	m_icon.loadFromFile("assets/icon1.png");
	m_window.setIcon(48, 48, m_icon.getPixelsPtr());
}

void Application::run()
{
	std::unique_ptr<State> state(new MenuState(m_window));
	//std::unique_ptr<State> state(new PlayState(m_window));

	while(state != nullptr)
		state = state->run();
}