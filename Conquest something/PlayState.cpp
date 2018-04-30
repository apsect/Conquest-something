#include "PlayState.h"
#include "MenuState.h"

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>

using sf::Color;
using sf::Text;
using sf::Event;
using sf::Keyboard;
using sf::Mouse;

PlayState::PlayState(sf::RenderWindow& a_window) :
	State(a_window),
	m_background(Color(0, 0, 0)),
	m_menu(sf::Vector2f(300.f, 200.f)),
	m_selection(3, 12),
	m_menuState(0),
	//m_cs(5.f),
	m_globalPosition(m_view.getCenter()),
	m_zoomFactor(0),
	m_pause(false)
	//m_buttonMode("assets/ButtonMode1.png", 626.f, 733.f, true),
{
	srand(static_cast<unsigned int>(time(0)));
	m_viewFixed.reset(sf::FloatRect(0.f, 0.f, 1024.f, 768.f));
	m_view = m_viewFixed;
	//m_view.setCenter(0.f, 0.f, );
	//m_view.setCenter(m_currentMap.getDataToCentralizeView(randomPlayerPos));

	m_minimap.reset(sf::FloatRect(0.f, 0.f, 2400.f, 1702.f));
	m_minimap.setViewport(sf::FloatRect(0.728515625f, 0.6927083f, 0.2431640625f, 0.2109375f));
	
	m_boundViewOnMinimap.setFillColor(Color(255, 255, 255, 32));
	m_boundViewOnMinimap.setOutlineThickness(10);
	m_boundViewOnMinimap.setOutlineColor(Color(0, 0, 0, 255));
	float centerX(m_view.getCenter().x), centerY(m_view.getCenter().y), 
		sizeX(m_view.getSize().x), sizeY(m_view.getSize().y);
	m_boundViewOnMinimap.setPosition(centerX - (sizeX / 2), centerY - (sizeY / 2));
	m_boundViewOnMinimap.setSize(m_view.getSize());

	m_font.loadFromFile("assets/FRAMDCN.ttf");
	/*m_time.setFont(m_font);
	m_time.setCharacterSize(24U);
	m_time.setColor(Color::Green);
	m_time.setPosition(10.f, 730.f);

	/*m_userPower.setFont(m_font);
	m_userPower.setCharacterSize(24U);
	m_userPower.setColor(Color::Green);
	m_userPower.setPosition(432.f, 13.f);*/

	// Menu
	m_menu.setFillColor(Color(0x44, 0x44, 0x44));
	m_menu.setPosition(106.f, 92.f);
	m_selection.setFillColor(Color(0x40, 0x00, 0x80));
	m_selection.setPosition(150.f, 133.f);

	m_texts.push_back(Text("Resume", m_font, 30U));
	m_texts.push_back(Text("Restart", m_font, 30U));
	m_texts.push_back(Text("Exit", m_font, 30U));
	float y = 120.f;
	for (auto text = m_texts.begin(); text != m_texts.end(); text++, y += 50)
	{
		text->setFillColor(Color(0x40, 0x00, 0x80));
		text->setPosition(180.f, y);
	}

	//Map
	m_tex_map.loadFromFile("map/background.png");
	m_spr_map.setTexture(m_tex_map);

	m_tex_guiMain.loadFromFile("assets/GuiMain.png");
	m_spr_guiMain.setTexture(m_tex_guiMain);
}

std::unique_ptr<State> PlayState::run()
{
	while(m_window.isOpen() && m_currentState.status != Restart && m_currentState.status != Exit)
	{
		update();
		render();
	}
	if(m_currentState.status == Restart)
		return std::unique_ptr<State>(new PlayState(m_window));

	return std::unique_ptr<State>(new MenuState(m_window));
}

void PlayState::update()
{
	sf::Vector2i pixelPos(Mouse::getPosition(m_window));
	Event event;

	while(m_window.pollEvent(event))
	{
		switch(event.type)
		{
		 case Event::Closed:
			m_window.close();
			break;

		 case Event::KeyPressed:
			/*if(event.key.code == sf::Keyboard::Escape)
			{
				if(m_currentState.status == Menu)
					std::swap(m_currentState.status, m_currentState.last);
				else
				{
					std::swap(m_currentState.status, m_currentState.last);
					m_currentState.status = Menu;
				}
			}
			else if(event.key.code == Keyboard::Down && m_currentState.status == Menu)
			{
				if(m_menuState < 2)
				{
					m_selection.move(0.f, 50.f);
					++m_menuState;
				}
			}
			else if(event.key.code == Keyboard::Up && m_currentState.status == Menu)
			{
				if(m_menuState > 0)
				{
					m_selection.move(0.f, -50.f);
					--m_menuState;
				}
			}
			else if(event.key.code == Keyboard::Return && m_currentState.status == Menu)
			{
				if(m_menuState == 0)
					std::swap(m_currentState.status, m_currentState.last);
				else if(m_menuState == 1)
				{
					std::swap(m_currentState.status, m_currentState.last);
					m_currentState.status = Restart;
				}
				else if(m_menuState == 2)
				{
					m_view.reset(sf::FloatRect(0.f, 0.f, 820.f, 640.f));
					m_currentState.status = Exit;
				}
			}
			else */if(event.key.code == Keyboard::R && m_currentState.status == Game)
			{
				m_currentState.status = Restart;
			}
			else if(event.key.code == Keyboard::Q && m_currentState.status == Game)
			{
				m_commander.addBot();
			}
			else if(event.key.code == Keyboard::E && m_currentState.status == Game)
			{
				system("cls");
			}
			else if(event.key.code == Keyboard::Num1 && m_currentState.status == Game)
			{
				m_commander.setDrawType(noDraw);
			}
			else if(event.key.code == Keyboard::Num2 && m_currentState.status == Game)
			{
				m_commander.setDrawType(ownerColor);
			}
			else if(event.key.code == Keyboard::Num3 && m_currentState.status == Game &&
					m_commander.isSelectedCountry())
			{
				m_commander.setDrawType(diplomacy);
			}
			else if(event.key.code == Keyboard::Num4 && m_currentState.status == Game &&
					m_commander.isSelectedCountry())	
			{
				m_commander.setDrawType(provNear);
			}
			else if(event.key.code == Keyboard::Escape && m_currentState.status == Game)
			{
				m_view.reset(sf::FloatRect(0.f, 0.f, 1024.f, 768.f));
				m_currentState.status = Exit;
			}
			else if(event.key.code == Keyboard::Space && m_currentState.status == Game)
			{
				 if (m_pause) 
				 {
					 m_pause = false;
					 cout << "Pause removed.\n";
				 }
				else 
				{
					m_pause = true;
					cout << "Pause set.\n";
				 }
				/*int tempV(m_human->checkVictory(m_currentMap));
				cout << "\nRoll!\nTurn " << ++m_turn << endl;
				if (!m_human->m_defeat)
				{
					if (tempV == m_sizeMap)
					{
						cout << "Human won.\n";
						break;
					}
					else if (!tempV)
					{
						cout << "Human defeat.\n";
						m_human->m_defeat = true;
						continue;
					}
					m_human->roll();
					//cout << m_currentMap.getFreeNearProv(m_human->getPlayerColor()) << endl;
				}

				for (int i = 0; i < m_bots.size(); i++)
				{
					if (!m_bots[i].m_defeat)
					{
						if ((tempV  = m_bots[i].checkVictory(m_currentMap)) == m_sizeMap)
						{
							cout << "Bot " << i + 1 << " won.\n";
							//for (auto i = m_bots.begin(); i != m_bots.end(); i++)
								//delete *i;
							m_bots.clear();
							break;
						}
						else if (!tempV)
						{
							cout << "Bot " << i + 1 << " defeat.\n";
							m_bots[i].m_defeat = true;
							continue;
						}
						m_bots[i].roll();

						if (m_bots[i].getPower() > 0)
							m_bots[i].addProv(m_currentMap, m_bots, m_human);
					}
				}*/
			}
			break;

		 case Event::MouseWheelMoved:
			{
				if (event.mouseWheel.delta &&
					(m_zoomFactor + event.mouseWheel.delta) < 20 &&
					(m_zoomFactor + event.mouseWheel.delta) > -5)
				{
					if (event.mouseWheel.delta > 0)
					{
						m_view.zoom(1.f/0.9f);
						++m_zoomFactor;
					}
					else
					{
						m_view.zoom(0.9f);
						--m_zoomFactor;
					}

					float centerX(m_view.getCenter().x), centerY(m_view.getCenter().y), 
						sizeX(m_view.getSize().x), sizeY(m_view.getSize().y);

					m_boundViewOnMinimap.setPosition(centerX - (sizeX / 2), centerY - (sizeY / 2));
					m_boundViewOnMinimap.setSize(m_view.getSize());
				}
			}
			break;

		 case Event::MouseButtonPressed:
			{
				if (event.key.code == Mouse::Left)
				{
					m_commander.clickHuman(m_view.getCenter(), pixelPos, m_window);

					/*
					if (!(int(buffColor.r) == 255 && int(buffColor.g) == 255 && 
						int(buffColor.b) == 255))
					{
						//if (!m_players.empty())
							m_human->addProv(buffColor, m_currentMap, m_bots);
						//cout << "done\n";
					}*/
				}
				else if (event.key.code == Mouse::Right)
					m_globalPosition = Mouse::getPosition(m_window);
			}
			break;
		}
	}

	if (!m_pause)
		m_commander.updateAI();
		/*for (auto iter = m_countries.begin(); iter != m_countries.end(); iter++)
		{
			iter->roll(m_clock.getElapsedTime().asSeconds());
			iter->addProv(m_currentMap);
		}

	m_buffTime << int(m_clock.getElapsedTime().asSeconds());
	m_time.setString("Time: " +  m_buffTime.str());
	m_buffTime.str("");
	m_buffTime.clear();*/

	/*m_buffTime << m_human->getPower();
	m_userPower.setString(m_buffTime.str());
	m_buffTime.str("");
	m_buffTime.clear();*/

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		sf::Vector2i localPosition(Mouse::getPosition(m_window));
		sf::Vector2f moveStep(float((m_globalPosition.x - localPosition.x) / 15), 
							  float((m_globalPosition.y - localPosition.y) / 15));

		sf::Vector2f temp(m_view.getCenter().x, m_view.getCenter().y);
		if (0 > m_view.getCenter().x)
		{
			temp.x = 0.f;
			m_view.setCenter(temp.x, temp.y);
		}
		if (0 > m_view.getCenter().y) 
		{
			temp.y = 0.f;
			m_view.setCenter(temp.x, temp.y);
		}
		if (m_view.getCenter().x > m_tex_map.getSize().x) 
		{
			temp.x = float(m_tex_map.getSize().x);
			m_view.setCenter(temp.x, temp.y);
		}
		if (m_view.getCenter().y > m_tex_map.getSize().y) 
		{
			temp.y = float(m_tex_map.getSize().y);
			m_view.setCenter(temp.x, temp.y);
		}

		m_view.move(moveStep.x, moveStep.y);
		float centerX(m_view.getCenter().x), centerY(m_view.getCenter().y), 
			sizeX(m_view.getSize().x), sizeY(m_view.getSize().y);
		m_boundViewOnMinimap.setPosition(centerX - (sizeX / 2), centerY - (sizeY / 2));
		m_boundViewOnMinimap.setSize(m_view.getSize());
	}
}

void PlayState::render()
{
	m_window.clear(Color(8, 8, 8));
	m_window.setView(m_view);
	if (m_currentState.status == Exit)
		return;
	m_window.draw(m_spr_map);
	m_commander.drawPlayers(m_window);
	//m_window.draw(m_time);

	m_window.setView(m_minimap);
	m_window.draw(m_spr_map);
	m_window.draw(m_boundViewOnMinimap);

	m_window.setView(m_viewFixed);
	m_window.draw(m_spr_guiMain);
	m_commander.drawInfoWnd(m_window);
	m_commander.drawMapModeView(m_window);
	//m_window.draw(m_time);
	//m_window.draw(m_userPower);
	m_window.setView(m_view);

	switch(m_currentState.status)
	{
	 case Menu:
		m_window.setView(m_viewFixed);
		m_window.draw(m_menu);
		m_window.draw(m_selection);
		for (auto text = m_texts.begin(); text != m_texts.end(); text++)
			m_window.draw(*text);
		m_window.setView(m_view);
		break;
	}

	m_window.display();
}
