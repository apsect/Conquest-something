#include "MenuState.h"
#include "PlayState.h"

#include <SFML/System/String.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>

using sf::Color;
using sf::Text;
using sf::Event;
using sf::Keyboard;
using sf::Mouse;

MenuState::MenuState(sf::RenderWindow& a_window) :
	State(a_window),
	m_selection(-1),
	m_status(Menu)
{
	m_offscreen.create(m_window.getSize().x, m_window.getSize().y);
	m_font.loadFromFile("assets/FRAMDCN.ttf");

	m_texts.push_back(Text("PLAY", m_font, 30U));
	m_texts.push_back(Text("ABOUT", m_font, 30U));
	m_texts.push_back(Text("EXIT", m_font, 30U));
	for (auto text = m_texts.begin(); text != m_texts.end(); text++)
	{
		m_shadows.push_back(*text);
		text->setStyle(Text::Bold);
		text->setFillColor(Color(64, 0, 128));
	}

	for (auto shadow = m_shadows.begin(); shadow != m_shadows.end(); shadow++)
		shadow->setFillColor(Color(64, 64, 64));

	m_shadows[0].setPosition(470.f, 272.f);
	m_texts[0].setPosition(468.f, 270.f);
	m_shadows[1].setPosition(456.f, 372.f);
	m_texts[1].setPosition(454.f, 370.f);
	m_shadows[2].setPosition(472.f, 472.f);
	m_texts[2].setPosition(470.f, 470.f);

	m_overlay.setTexture(m_offscreen.getTexture());
	//m_overlay.setOrigin(0.f, 50.f);
	//m_overlay.setPosition(90.f, 88.f);

	m_tex_highlight.loadFromFile("assets/highlight2.png");
	m_spr_highlight.setTexture(m_tex_highlight);
	m_spr_highlight.setPosition(368.f, 240.f);

	m_tex_about.loadFromFile("assets/credits1.png");
	m_spr_about.setTexture(m_tex_about);

	m_tex_backgroudMenu.loadFromFile("assets/backgroundMenu.png");
	m_spr_backgroudMenu.setTexture(m_tex_backgroudMenu);
	m_tex_backgroudMenu1.loadFromFile("assets/backgroundMenu1.png");
	m_spr_backgroudMenu1.setTexture(m_tex_backgroudMenu1);
	m_tex_backgroudMenu2.loadFromFile("assets/backgroundMenu2.png");
	m_spr_backgroudMenu2.setTexture(m_tex_backgroudMenu2);
}

std::unique_ptr<State> MenuState::run()
{
	while(m_window.isOpen() && m_status != Play && m_status != Exit)
	{
		update();
		render();
	}

	if(m_status == Play)
		return std::unique_ptr<State>(new PlayState(m_window));

	return nullptr;
}

void MenuState::update()
{
	sf::Vector2i pixelPos = Mouse::getPosition(m_window);
	sf::Vector2f pos = m_window.mapPixelToCoords(pixelPos);

	Event event;
	while(m_window.pollEvent(event))
	{
		switch(event.type)
		{
		 case Event::Closed:
			m_window.close();
			break;

		 case Event::MouseMoved:
			for (int i = 0, size = static_cast<int>(m_texts.size()); i < size; i++)
				if (m_texts[i].getGlobalBounds().contains(pos.x, pos.y))
				{
					if (m_selection == -1) m_selection = 0;
					m_spr_highlight.move(0, (i - m_selection) * 100.f);					
					m_selection = i;
					break;
				}
				else if (i == size - 1 &&  m_selection != -1) 
				{
					m_selection = -1;
					m_spr_highlight.setPosition(368.f, 240.f);
				}
			break;

		 case Event::MouseButtonPressed:
			if (event.key.code == Mouse::Left)
			{
				std::cout << m_selection << std::endl;
				switch(m_selection)
				{
				 case 0:
					m_status = Play;
					break;

				 case 1:
					m_status = About;
					break;

				 case 2:
					m_status = Exit;
					break;
				}
			}

		 case Event::KeyPressed:
			if(event.key.code == Keyboard::Escape)
			{
				if(m_status == About)
					m_status = Menu;
				else if(m_status == Menu)
					m_status = Exit;
			}
		}
	}
}

void MenuState::render()
{
	m_offscreen.clear(Color(0, 0, 0, 75));
	if (m_selection != -1)	
		m_offscreen.draw(m_spr_highlight, sf::BlendNone);
	m_offscreen.display();

	m_window.clear();
	m_window.draw(m_spr_backgroudMenu);
	m_window.draw(m_spr_backgroudMenu1);

	for(auto shadow = m_shadows.begin(); shadow != m_shadows.end(); shadow++)
		m_window.draw(*shadow);
	for(auto text = m_texts.begin(); text != m_texts.end(); text++)
		m_window.draw(*text);

	m_window.draw(m_overlay);
	if(m_status == About) 
		m_window.draw(m_spr_about);
	m_window.draw(m_spr_backgroudMenu2);

	m_window.display();
}