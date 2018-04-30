#pragma once

#include "State.h"
//#include "Map.h"
//#include "Country.h"
#include "RelationshipManager.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

#include <vector>
#include <random>

class PlayState : public State
{
public:
	PlayState(sf::RenderWindow &a_window);
	~PlayState();
	std::unique_ptr<State> run();

private:
	void update();
	void render();

private:
	enum Status
	{
		Game,
		Menu,
		Restart,
		Exit
	};

	struct GameState
	{
		GameState() 
		{
			status = Game;
			last = Exit;
		}
		Status status;
		Status last;
	};

	// Menu
	sf::RectangleShape m_menu;
	sf::CircleShape m_selection;
	sf::Text m_resume;
	sf::Text m_restart;
	sf::Text m_exit;
	int m_menuState;

	GameState m_currentState; 
	sf::Color m_background;
	sf::Font m_font;
	
	//std::ostringstream m_buffTime;
	//sf::Text m_time;
	std::vector<sf::Text> m_texts;

	sf::View m_view;
	sf::View m_viewFixed;
	sf::Vector2i m_globalPosition;
	//sf::CircleShape m_cs;
	int m_zoomFactor;

	sf::Texture m_tex_map;
	sf::Sprite m_spr_map;

	bool m_pause;
	CRelationshipManager m_commander;

	sf::Texture m_tex_guiMain;
	sf::Sprite m_spr_guiMain;
	sf::RectangleShape m_boundViewOnMinimap;

	sf::View m_minimap;
};