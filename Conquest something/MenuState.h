#pragma once

#include "State.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <map>
#include <string>
#include <vector>

class MenuState : public State
{
public:
	MenuState(sf::RenderWindow& a_window);
	std::unique_ptr<State> run();

private:
	void update();
	void render();

private:
	enum Status
	{
		Menu,
		Play,
		About,
		Exit
	};

	sf::RenderTexture m_offscreen;

	sf::Font m_font;
	std::vector<sf::Text> m_texts;
	std::vector<sf::Text> m_shadows;

	sf::Sprite m_overlay;
	int m_selection;

	sf::Texture m_tex_highlight;
	sf::Sprite m_spr_highlight;

	sf::Texture m_tex_about;
	sf::Sprite m_spr_about;

	sf::Texture m_tex_backgroudMenu;
	sf::Sprite m_spr_backgroudMenu;

	sf::Texture m_tex_backgroudMenu1;
	sf::Sprite m_spr_backgroudMenu1;

	sf::Texture m_tex_backgroudMenu2;
	sf::Sprite m_spr_backgroudMenu2;

	sf::Texture m_tex_guiMain;
	sf::Sprite m_spr_guiMain;

	Status m_status;
};